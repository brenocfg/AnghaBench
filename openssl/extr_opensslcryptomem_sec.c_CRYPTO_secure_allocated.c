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

int CRYPTO_secure_allocated(const void *ptr)
{
#ifdef OPENSSL_SECURE_MEMORY
    int ret;

    if (!secure_mem_initialized)
        return 0;
    CRYPTO_THREAD_write_lock(sec_malloc_lock);
    ret = sh_allocated(ptr);
    CRYPTO_THREAD_unlock(sec_malloc_lock);
    return ret;
#else
    return 0;
#endif /* OPENSSL_SECURE_MEMORY */
}