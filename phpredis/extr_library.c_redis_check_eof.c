#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ status; scalar_t__ mode; long retry_interval; scalar_t__ dbNumber; scalar_t__ auth; scalar_t__ stream; scalar_t__ watching; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 scalar_t__ MULTI ; 
 scalar_t__ REDIS_SOCK_STATUS_FAILED ; 
 int /*<<< orphan*/  REDIS_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 long php_rand () ; 
 scalar_t__ php_stream_eof (scalar_t__) ; 
 scalar_t__ redis_sock_auth (TYPE_1__*) ; 
 scalar_t__ redis_sock_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  redis_sock_disconnect (TYPE_1__*,int) ; 
 scalar_t__ reselect_db (TYPE_1__*) ; 
 int /*<<< orphan*/  usleep (long) ; 

int
redis_check_eof(RedisSock *redis_sock, int no_throw)
{
    int count;
    char *errmsg;

    if (!redis_sock || !redis_sock->stream || redis_sock->status == REDIS_SOCK_STATUS_FAILED) {
        if (!no_throw) {
            REDIS_THROW_EXCEPTION( "Connection closed", 0);
        }
        return -1;
    }

    /* NOITCE: set errno = 0 here
     *
     * There is a bug in php socket stream to check liveness of a connection:
     * if (0 >= recv(sock->socket, &buf, sizeof(buf), MSG_PEEK) && php_socket_errno() != EWOULDBLOCK) {
     *    alive = 0;
     * }
     * If last errno is EWOULDBLOCK and recv returns 0 because of connection closed, alive would not be
     * set to 0. However, the connection is close indeed. The php_stream_eof is not reliable. This will
     * cause a "read error on connection" exception when use a closed persistent connection.
     *
     * We work around this by set errno = 0 first.
     *
     * Bug fix of php: https://github.com/php/php-src/pull/1456
     * */
    errno = 0;
    if (php_stream_eof(redis_sock->stream) == 0) {
        /* Success */
        return 0;
    } else if (redis_sock->mode == MULTI || redis_sock->watching) {
        errmsg = "Connection lost and socket is in MULTI/watching mode";
    } else {
        errmsg = "Connection lost";
        /* TODO: configurable max retry count */
        for (count = 0; count < 10; ++count) {
            /* close existing stream before reconnecting */
            if (redis_sock->stream) {
                redis_sock_disconnect(redis_sock, 1);
            }
            // Wait for a while before trying to reconnect
            if (redis_sock->retry_interval) {
                // Random factor to avoid having several (or many) concurrent connections trying to reconnect at the same time
                long retry_interval = (count ? redis_sock->retry_interval : (php_rand() % redis_sock->retry_interval));
                usleep(retry_interval);
            }
            /* reconnect */
            if (redis_sock_connect(redis_sock) == 0) {
                /* check for EOF again. */
                errno = 0;
                if (php_stream_eof(redis_sock->stream) == 0) {
                    /* If we're using a password, attempt a reauthorization */
                    if (redis_sock->auth && redis_sock_auth(redis_sock) != 0) {
                        errmsg = "AUTH failed while reconnecting";
                        break;
                    }
                    /* If we're using a non-zero db, reselect it */
                    if (redis_sock->dbNumber && reselect_db(redis_sock) != 0) {
                        errmsg = "SELECT failed while reconnecting";
                        break;
                    }
                    /* Success */
                    return 0;
                }
            }
        }
    }
    /* close stream and mark socket as failed */
    redis_sock_disconnect(redis_sock, 1);
    redis_sock->status = REDIS_SOCK_STATUS_FAILED;
    if (!no_throw) {
        REDIS_THROW_EXCEPTION( errmsg, 0);
    }
    return -1;
}