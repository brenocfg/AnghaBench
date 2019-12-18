#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ port; int /*<<< orphan*/  host; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_THROW_EXCEPTION (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/ * php_stream_get_line (int /*<<< orphan*/ ,char*,int,size_t*) ; 
 int redis_check_eof (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_sock_disconnect (TYPE_1__*,int) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int
redis_sock_gets(RedisSock *redis_sock, char *buf, int buf_size,
                size_t *line_size)
{
    // Handle EOF
    if(-1 == redis_check_eof(redis_sock, 0)) {
        return -1;
    }

    if(php_stream_get_line(redis_sock->stream, buf, buf_size, line_size)
                           == NULL)
    {
        char *errmsg = NULL;

        if (redis_sock->port < 0) {
            spprintf(&errmsg, 0, "read error on connection to %s", ZSTR_VAL(redis_sock->host));
        } else {
            spprintf(&errmsg, 0, "read error on connection to %s:%d", ZSTR_VAL(redis_sock->host), redis_sock->port);
        }
        // Close our socket
        redis_sock_disconnect(redis_sock, 1);

        // Throw a read error exception
        REDIS_THROW_EXCEPTION(errmsg, 0);
        efree(errmsg);
        return -1;
    }

    /* We don't need \r\n */
    *line_size-=2;
    buf[*line_size]='\0';

    /* Success! */
    return 0;
}