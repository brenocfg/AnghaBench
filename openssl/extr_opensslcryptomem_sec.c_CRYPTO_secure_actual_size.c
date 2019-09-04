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

size_t CRYPTO_secure_actual_size(void *ptr)
{
#ifdef OPENSSL_SECURE_MEMORY
    size_t actual_size;

    CRYPTO_THREAD_write_lock(sec_malloc_lock);
    actual_size = sh_actual_size(ptr);
    CRYPTO_THREAD_unlock(sec_malloc_lock);
    return actual_size;
#else
    return 0;
#endif
}