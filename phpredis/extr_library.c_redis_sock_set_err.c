#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * err; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/ * zend_string_init (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 

void
redis_sock_set_err(RedisSock *redis_sock, const char *msg, int msg_len)
{
    // Free our last error
    if (redis_sock->err != NULL) {
        zend_string_release(redis_sock->err);
        redis_sock->err = NULL;
    }

    if (msg != NULL && msg_len > 0) {
        // Copy in our new error message
        redis_sock->err = zend_string_init(msg, msg_len, 0);
    }
}