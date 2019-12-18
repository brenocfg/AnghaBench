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
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 size_t php_stream_write (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ redis_check_eof (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
redis_sock_write(RedisSock *redis_sock, char *cmd, size_t sz)
{
    if (redis_check_eof(redis_sock, 0) == 0 &&
        php_stream_write(redis_sock->stream, cmd, sz) == sz
    ) {
        return sz;
    }
    return -1;
}