#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  libctx; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 size_t BN_num_bytes (int /*<<< orphan*/ *) ; 
 int EC_FLAG_COFACTOR_ECDH ; 
 int /*<<< orphan*/  EC_F_ECDH_SIMPLE_COMPUTE_KEY ; 
 int /*<<< orphan*/  EC_GROUP_get_cofactor (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_degree (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (TYPE_1__ const*) ; 
 int EC_KEY_get_flags (TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_POINT_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  EC_R_POINT_ARITHMETIC_FAILURE ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

int ecdh_simple_compute_key(unsigned char **pout, size_t *poutlen,
                            const EC_POINT *pub_key, const EC_KEY *ecdh)
{
    BN_CTX *ctx;
    EC_POINT *tmp = NULL;
    BIGNUM *x = NULL;
    const BIGNUM *priv_key;
    const EC_GROUP *group;
    int ret = 0;
    size_t buflen, len;
    unsigned char *buf = NULL;

    if ((ctx = BN_CTX_new_ex(ecdh->libctx)) == NULL)
        goto err;
    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    if (x == NULL) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    priv_key = EC_KEY_get0_private_key(ecdh);
    if (priv_key == NULL) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, EC_R_MISSING_PRIVATE_KEY);
        goto err;
    }

    group = EC_KEY_get0_group(ecdh);

    if (EC_KEY_get_flags(ecdh) & EC_FLAG_COFACTOR_ECDH) {
        if (!EC_GROUP_get_cofactor(group, x, NULL) ||
            !BN_mul(x, x, priv_key, ctx)) {
            ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        priv_key = x;
    }

    if ((tmp = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (!EC_POINT_mul(group, tmp, NULL, pub_key, priv_key, ctx)) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, EC_R_POINT_ARITHMETIC_FAILURE);
        goto err;
    }

    if (!EC_POINT_get_affine_coordinates(group, tmp, x, NULL, ctx)) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, EC_R_POINT_ARITHMETIC_FAILURE);
        goto err;
    }

    buflen = (EC_GROUP_get_degree(group) + 7) / 8;
    len = BN_num_bytes(x);
    if (len > buflen) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_INTERNAL_ERROR);
        goto err;
    }
    if ((buf = OPENSSL_malloc(buflen)) == NULL) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    memset(buf, 0, buflen - len);
    if (len != (size_t)BN_bn2bin(x, buf + buflen - len)) {
        ECerr(EC_F_ECDH_SIMPLE_COMPUTE_KEY, ERR_R_BN_LIB);
        goto err;
    }

    *pout = buf;
    *poutlen = buflen;
    buf = NULL;

    ret = 1;

 err:
    EC_POINT_clear_free(tmp);
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    OPENSSL_free(buf);
    return ret;
}