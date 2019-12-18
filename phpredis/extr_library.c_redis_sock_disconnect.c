#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  list; int /*<<< orphan*/  nb_active; } ;
struct TYPE_6__ {scalar_t__ watching; int /*<<< orphan*/  status; int /*<<< orphan*/  mode; int /*<<< orphan*/ * stream; scalar_t__ persistent; } ;
typedef  TYPE_1__ RedisSock ;
typedef  TYPE_2__ ConnectionPool ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC ; 
 int FAILURE ; 
 scalar_t__ INI_INT (char*) ; 
 int /*<<< orphan*/  REDIS_SOCK_STATUS_DISCONNECTED ; 
 int SUCCESS ; 
 int /*<<< orphan*/  php_stream_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_stream_pclose (int /*<<< orphan*/ *) ; 
 TYPE_2__* redis_sock_get_connection_pool (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_llist_prepend_element (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int
redis_sock_disconnect(RedisSock *redis_sock, int force)
{
    if (redis_sock == NULL) {
        return FAILURE;
    } else if (redis_sock->stream) {
        if (redis_sock->persistent) {
            ConnectionPool *p = NULL;
            if (INI_INT("redis.pconnect.pooling_enabled")) {
                p = redis_sock_get_connection_pool(redis_sock);
            }
            if (force) {
                php_stream_pclose(redis_sock->stream);
                if (p) p->nb_active--;
            } else if (p) {
                zend_llist_prepend_element(&p->list, &redis_sock->stream);
            }
        } else {
            php_stream_close(redis_sock->stream);
        }
        redis_sock->stream = NULL;
    }
    redis_sock->mode = ATOMIC;
    redis_sock->status = REDIS_SOCK_STATUS_DISCONNECTED;
    redis_sock->watching = 0;

    return SUCCESS;
}