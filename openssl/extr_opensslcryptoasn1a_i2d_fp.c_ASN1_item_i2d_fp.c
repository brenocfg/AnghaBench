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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  BIO ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_I2D_FP ; 
 int ASN1_item_i2d_bio (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_NOCLOSE ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_file () ; 
 int /*<<< orphan*/  BIO_set_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BUF_LIB ; 

int ASN1_item_i2d_fp(const ASN1_ITEM *it, FILE *out, const void *x)
{
    BIO *b;
    int ret;

    if ((b = BIO_new(BIO_s_file())) == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_I2D_FP, ERR_R_BUF_LIB);
        return 0;
    }
    BIO_set_fp(b, out, BIO_NOCLOSE);
    ret = ASN1_item_i2d_bio(it, b, x);
    BIO_free(b);
    return ret;
}