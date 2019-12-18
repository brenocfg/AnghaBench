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
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_write (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PEM_F_I2B_PVK_BIO ; 
 int /*<<< orphan*/  PEM_R_BIO_WRITE_FAILURE ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2b_PVK (unsigned char**,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void*) ; 

int i2b_PVK_bio(BIO *out, EVP_PKEY *pk, int enclevel,
                pem_password_cb *cb, void *u)
{
    unsigned char *tmp = NULL;
    int outlen, wrlen;
    outlen = i2b_PVK(&tmp, pk, enclevel, cb, u);
    if (outlen < 0)
        return -1;
    wrlen = BIO_write(out, tmp, outlen);
    OPENSSL_free(tmp);
    if (wrlen == outlen) {
        PEMerr(PEM_F_I2B_PVK_BIO, PEM_R_BIO_WRITE_FAILURE);
        return outlen;
    }
    return -1;
}