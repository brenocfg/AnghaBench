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
struct TYPE_4__ {int /*<<< orphan*/ * err; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_SOCK_ERRCMP_STATIC (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  REDIS_THROW_EXCEPTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
redis_error_throw(RedisSock *redis_sock)
{
    /* Short circuit if we have no redis_sock or any error */
    if (redis_sock == NULL || redis_sock->err == NULL)
        return;

    /* We may want to flip this logic and check for MASTERDOWN, AUTH,
     * and LOADING but that may have side effects (esp for things like
     * Disque) */
    if (!REDIS_SOCK_ERRCMP_STATIC(redis_sock, "ERR") &&
        !REDIS_SOCK_ERRCMP_STATIC(redis_sock, "NOSCRIPT") &&
        !REDIS_SOCK_ERRCMP_STATIC(redis_sock, "WRONGTYPE") &&
        !REDIS_SOCK_ERRCMP_STATIC(redis_sock, "BUSYGROUP") &&
        !REDIS_SOCK_ERRCMP_STATIC(redis_sock, "NOGROUP"))
    {
        REDIS_THROW_EXCEPTION( ZSTR_VAL(redis_sock->err), 0);
    }
}