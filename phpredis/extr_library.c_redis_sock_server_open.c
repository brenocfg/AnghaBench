#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int FAILURE ; 
#define  REDIS_SOCK_STATUS_DISCONNECTED 129 
#define  REDIS_SOCK_STATUS_FAILED 128 
 int SUCCESS ; 
 int redis_sock_connect (TYPE_1__*) ; 

int
redis_sock_server_open(RedisSock *redis_sock)
{
    if (redis_sock) {
        switch (redis_sock->status) {
        case REDIS_SOCK_STATUS_FAILED:
            return FAILURE;
        case REDIS_SOCK_STATUS_DISCONNECTED:
            return redis_sock_connect(redis_sock);
        default:
            return SUCCESS;
        }
    }
    return FAILURE;
}