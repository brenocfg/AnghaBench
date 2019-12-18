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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int /*<<< orphan*/  PEM_F_D2I_PKCS8PRIVATEKEY_FP ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_PKCS8PrivateKey_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*) ; 

EVP_PKEY *d2i_PKCS8PrivateKey_fp(FILE *fp, EVP_PKEY **x, pem_password_cb *cb,
                                 void *u)
{
    BIO *bp;
    EVP_PKEY *ret;

    if ((bp = BIO_new_fp(fp, BIO_NOCLOSE)) == NULL) {
        PEMerr(PEM_F_D2I_PKCS8PRIVATEKEY_FP, ERR_R_BUF_LIB);
        return NULL;
    }
    ret = d2i_PKCS8PrivateKey_bio(bp, x, cb, u);
    BIO_free(bp);
    return ret;
}