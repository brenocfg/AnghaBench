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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_memdup (char const*,int) ; 
 int /*<<< orphan*/  TEST_ptr (char*) ; 
 int /*<<< orphan*/  copy_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ docorrupt ; 

__attribute__((used)) static int tls_corrupt_write(BIO *bio, const char *in, int inl)
{
    int ret;
    BIO *next = BIO_next(bio);
    char *copy;

    if (docorrupt) {
        if (!TEST_ptr(copy = OPENSSL_memdup(in, inl)))
            return 0;
        /* corrupt last bit of application data */
        copy[inl-1] ^= 1;
        ret = BIO_write(next, copy, inl);
        OPENSSL_free(copy);
    } else {
        ret = BIO_write(next, in, inl);
    }
    copy_flags(bio);

    return ret;
}