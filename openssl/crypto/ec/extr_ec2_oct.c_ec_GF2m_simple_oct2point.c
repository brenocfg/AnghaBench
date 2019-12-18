#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int point_conversion_form_t ;
struct TYPE_10__ {TYPE_1__* meth; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* field_div ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char const*,size_t,int /*<<< orphan*/ *) ; 
 int BN_is_odd (int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_OCT2POINT ; 
 int EC_GROUP_get_degree (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_set_compressed_coordinates (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int EC_POINT_set_to_infinity (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EC_R_INVALID_ENCODING ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int POINT_CONVERSION_COMPRESSED ; 
 int POINT_CONVERSION_HYBRID ; 
 int POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int ec_GF2m_simple_oct2point(const EC_GROUP *group, EC_POINT *point,
                             const unsigned char *buf, size_t len,
                             BN_CTX *ctx)
{
    point_conversion_form_t form;
    int y_bit, m;
    BIGNUM *x, *y, *yxi;
    size_t field_len, enc_len;
    int ret = 0;
#ifndef FIPS_MODE
    BN_CTX *new_ctx = NULL;
#endif

    if (len == 0) {
        ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_BUFFER_TOO_SMALL);
        return 0;
    }
    form = buf[0];
    y_bit = form & 1;
    form = form & ~1U;
    if ((form != 0) && (form != POINT_CONVERSION_COMPRESSED)
        && (form != POINT_CONVERSION_UNCOMPRESSED)
        && (form != POINT_CONVERSION_HYBRID)) {
        ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
        return 0;
    }
    if ((form == 0 || form == POINT_CONVERSION_UNCOMPRESSED) && y_bit) {
        ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
        return 0;
    }

    if (form == 0) {
        if (len != 1) {
            ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
            return 0;
        }

        return EC_POINT_set_to_infinity(group, point);
    }

    m = EC_GROUP_get_degree(group);
    field_len = (m + 7) / 8;
    enc_len =
        (form ==
         POINT_CONVERSION_COMPRESSED) ? 1 + field_len : 1 + 2 * field_len;

    if (len != enc_len) {
        ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
        return 0;
    }

#ifndef FIPS_MODE
    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL)
            return 0;
    }
#endif

    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    yxi = BN_CTX_get(ctx);
    if (yxi == NULL)
        goto err;

    if (!BN_bin2bn(buf + 1, field_len, x))
        goto err;
    if (BN_num_bits(x) > m) {
        ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
        goto err;
    }

    if (form == POINT_CONVERSION_COMPRESSED) {
        if (!EC_POINT_set_compressed_coordinates(group, point, x, y_bit, ctx))
            goto err;
    } else {
        if (!BN_bin2bn(buf + 1 + field_len, field_len, y))
            goto err;
        if (BN_num_bits(y) > m) {
            ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
            goto err;
        }
        if (form == POINT_CONVERSION_HYBRID) {
            if (!group->meth->field_div(group, yxi, y, x, ctx))
                goto err;
            if (y_bit != BN_is_odd(yxi)) {
                ECerr(EC_F_EC_GF2M_SIMPLE_OCT2POINT, EC_R_INVALID_ENCODING);
                goto err;
            }
        }

        /*
         * EC_POINT_set_affine_coordinates is responsible for checking that
         * the point is on the curve.
         */
        if (!EC_POINT_set_affine_coordinates(group, point, x, y, ctx))
            goto err;
    }

    ret = 1;

 err:
    BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(new_ctx);
#endif
    return ret;
}