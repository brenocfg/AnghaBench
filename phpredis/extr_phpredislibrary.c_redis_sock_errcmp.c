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
struct TYPE_3__ {int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 size_t ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int redis_sock_errcmp(RedisSock *redis_sock, const char *err, size_t errlen) {
    return ZSTR_LEN(redis_sock->err) >= errlen &&
           memcmp(ZSTR_VAL(redis_sock->err), err, errlen) == 0;
}