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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int do_i2b (unsigned char**,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int do_i2b_bio(BIO *out, EVP_PKEY *pk, int ispub)
{
    unsigned char *tmp = NULL;
    int outlen, wrlen;
    outlen = do_i2b(&tmp, pk, ispub);
    if (outlen < 0)
        return -1;
    wrlen = BIO_write(out, tmp, outlen);
    OPENSSL_free(tmp);
    if (wrlen == outlen)
        return outlen;
    return -1;
}