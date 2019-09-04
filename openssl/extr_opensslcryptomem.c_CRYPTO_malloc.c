#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_mem_debug_malloc (void*,size_t,int,char const*,int) ; 
 int /*<<< orphan*/  FAILTEST () ; 
 int /*<<< orphan*/  INCREMENT (int /*<<< orphan*/ ) ; 
 scalar_t__ allow_customize ; 
 scalar_t__ call_malloc_debug ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  malloc_count ; 
 void* malloc_impl (size_t,char const*,int) ; 

void *CRYPTO_malloc(size_t num, const char *file, int line)
{
    void *ret = NULL;

    INCREMENT(malloc_count);
    if (malloc_impl != NULL && malloc_impl != CRYPTO_malloc)
        return malloc_impl(num, file, line);

    if (num == 0)
        return NULL;

    FAILTEST();
    if (allow_customize) {
        /*
         * Disallow customization after the first allocation. We only set this
         * if necessary to avoid a store to the same cache line on every
         * allocation.
         */
        allow_customize = 0;
    }
#if !defined(OPENSSL_NO_CRYPTO_MDEBUG) && !defined(FIPS_MODE)
    if (call_malloc_debug) {
        CRYPTO_mem_debug_malloc(NULL, num, 0, file, line);
        ret = malloc(num);
        CRYPTO_mem_debug_malloc(ret, num, 1, file, line);
    } else {
        ret = malloc(num);
    }
#else
    (void)(file); (void)(line);
    ret = malloc(num);
#endif

    return ret;
}