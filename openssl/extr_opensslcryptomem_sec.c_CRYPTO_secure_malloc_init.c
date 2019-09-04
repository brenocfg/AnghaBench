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

int CRYPTO_secure_malloc_init(size_t size, int minsize)
{
#ifdef OPENSSL_SECURE_MEMORY
    int ret = 0;

    if (!secure_mem_initialized) {
        sec_malloc_lock = CRYPTO_THREAD_lock_new();
        if (sec_malloc_lock == NULL)
            return 0;
        if ((ret = sh_init(size, minsize)) != 0) {
            secure_mem_initialized = 1;
        } else {
            CRYPTO_THREAD_lock_free(sec_malloc_lock);
            sec_malloc_lock = NULL;
        }
    }

    return ret;
#else
    return 0;
#endif /* OPENSSL_SECURE_MEMORY */
}