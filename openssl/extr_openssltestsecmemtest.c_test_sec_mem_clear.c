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

__attribute__((used)) static int test_sec_mem_clear(void)
{
#ifdef OPENSSL_SECURE_MEMORY
    const int size = 64;
    unsigned char *p = NULL;
    int i, res = 0;

    if (!TEST_true(CRYPTO_secure_malloc_init(4096, 32))
            || !TEST_ptr(p = OPENSSL_secure_malloc(size)))
        goto err;

    for (i = 0; i < size; i++)
        if (!TEST_uchar_eq(p[i], 0))
            goto err;

    for (i = 0; i < size; i++)
        p[i] = (unsigned char)(i + ' ' + 1);

    OPENSSL_secure_free(p);

    /*
     * A deliberate use after free here to verify that the memory has been
     * cleared properly.  Since secure free doesn't return the memory to
     * libc's memory pool, it technically isn't freed.  However, the header
     * bytes have to be skipped and these consist of two pointers in the
     * current implementation.
     */
    for (i = sizeof(void *) * 2; i < size; i++)
        if (!TEST_uchar_eq(p[i], 0))
            return 0;

    res = 1;
    p = NULL;
err:
    OPENSSL_secure_free(p);
    CRYPTO_secure_malloc_done();
    return res;
#else
    return 1;
#endif
}