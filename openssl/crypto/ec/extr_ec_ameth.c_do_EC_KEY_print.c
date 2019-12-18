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
typedef  scalar_t__ ec_print_t ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ ASN1_buf_print (int /*<<< orphan*/ *,unsigned char*,size_t,int) ; 
 int /*<<< orphan*/  BIO_indent (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ BIO_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ECPKParameters_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EC_F_DO_EC_KEY_PRINT ; 
 int /*<<< orphan*/  EC_GROUP_order_bits (int /*<<< orphan*/  const*) ; 
 scalar_t__ EC_KEY_PRINT_PARAM ; 
 scalar_t__ EC_KEY_PRINT_PRIVATE ; 
 scalar_t__ EC_KEY_PRINT_PUBLIC ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_get_conv_form (int /*<<< orphan*/  const*) ; 
 size_t EC_KEY_key2buf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 size_t EC_KEY_priv2buf (int /*<<< orphan*/  const*,unsigned char**) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 

__attribute__((used)) static int do_EC_KEY_print(BIO *bp, const EC_KEY *x, int off, ec_print_t ktype)
{
    const char *ecstr;
    unsigned char *priv = NULL, *pub = NULL;
    size_t privlen = 0, publen = 0;
    int ret = 0;
    const EC_GROUP *group;

    if (x == NULL || (group = EC_KEY_get0_group(x)) == NULL) {
        ECerr(EC_F_DO_EC_KEY_PRINT, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (ktype != EC_KEY_PRINT_PARAM && EC_KEY_get0_public_key(x) != NULL) {
        publen = EC_KEY_key2buf(x, EC_KEY_get_conv_form(x), &pub, NULL);
        if (publen == 0)
            goto err;
    }

    if (ktype == EC_KEY_PRINT_PRIVATE && EC_KEY_get0_private_key(x) != NULL) {
        privlen = EC_KEY_priv2buf(x, &priv);
        if (privlen == 0)
            goto err;
    }

    if (ktype == EC_KEY_PRINT_PRIVATE)
        ecstr = "Private-Key";
    else if (ktype == EC_KEY_PRINT_PUBLIC)
        ecstr = "Public-Key";
    else
        ecstr = "ECDSA-Parameters";

    if (!BIO_indent(bp, off, 128))
        goto err;
    if (BIO_printf(bp, "%s: (%d bit)\n", ecstr,
                   EC_GROUP_order_bits(group)) <= 0)
        goto err;

    if (privlen != 0) {
        if (BIO_printf(bp, "%*spriv:\n", off, "") <= 0)
            goto err;
        if (ASN1_buf_print(bp, priv, privlen, off + 4) == 0)
            goto err;
    }

    if (publen != 0) {
        if (BIO_printf(bp, "%*spub:\n", off, "") <= 0)
            goto err;
        if (ASN1_buf_print(bp, pub, publen, off + 4) == 0)
            goto err;
    }

    if (!ECPKParameters_print(bp, group, off))
        goto err;
    ret = 1;
 err:
    if (!ret)
        ECerr(EC_F_DO_EC_KEY_PRINT, ERR_R_EC_LIB);
    OPENSSL_clear_free(priv, privlen);
    OPENSSL_free(pub);
    return ret;
}