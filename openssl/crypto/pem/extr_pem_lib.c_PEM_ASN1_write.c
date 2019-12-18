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
typedef  int /*<<< orphan*/  i2d_of_void ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 
 int PEM_ASN1_write_bio (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/  const*,unsigned char*,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  PEM_F_PEM_ASN1_WRITE ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PEM_ASN1_write(i2d_of_void *i2d, const char *name, FILE *fp,
                   void *x, const EVP_CIPHER *enc, unsigned char *kstr,
                   int klen, pem_password_cb *callback, void *u)
{
    BIO *b;
    int ret;

    if ((b = BIO_new(BIO_s_file())) == NULL) {
        PEMerr(PEM_F_PEM_ASN1_WRITE, ERR_R_BUF_LIB);
        return 0;
    }
    BIO_set_fp(b, fp, BIO_NOCLOSE);
    ret = PEM_ASN1_write_bio(i2d, name, b, x, enc, kstr, klen, callback, u);
    BIO_free(b);
    return ret;
}