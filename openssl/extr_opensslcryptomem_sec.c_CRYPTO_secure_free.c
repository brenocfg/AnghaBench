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
 int /*<<< orphan*/  CRYPTO_free (void*,char const*,int) ; 

void CRYPTO_secure_free(void *ptr, const char *file, int line)
{
#ifdef OPENSSL_SECURE_MEMORY
    size_t actual_size;

    if (ptr == NULL)
        return;
    if (!CRYPTO_secure_allocated(ptr)) {
        CRYPTO_free(ptr, file, line);
        return;
    }
    CRYPTO_THREAD_write_lock(sec_malloc_lock);
    actual_size = sh_actual_size(ptr);
    CLEAR(ptr, actual_size);
    secure_mem_used -= actual_size;
    sh_free(ptr);
    CRYPTO_THREAD_unlock(sec_malloc_lock);
#else
    CRYPTO_free(ptr, file, line);
#endif /* OPENSSL_SECURE_MEMORY */
}