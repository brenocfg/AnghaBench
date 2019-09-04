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

int CRYPTO_secure_malloc_initialized(void)
{
#ifdef OPENSSL_SECURE_MEMORY
    return secure_mem_initialized;
#else
    return 0;
#endif /* OPENSSL_SECURE_MEMORY */
}