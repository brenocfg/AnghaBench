#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char point_conversion_form_t ;
struct TYPE_9__ {TYPE_1__* meth; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* field_div ) (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
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
 size_t BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/ *) ; 
 size_t BN_num_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_F_EC_GF2M_SIMPLE_POINT2OCT ; 
 int EC_GROUP_get_degree (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_at_infinity (TYPE_2__ const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_BUFFER_TOO_SMALL ; 
 int /*<<< orphan*/  EC_R_INVALID_FORM ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 unsigned char POINT_CONVERSION_COMPRESSED ; 
 unsigned char POINT_CONVERSION_HYBRID ; 
 unsigned char POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

size_t ec_GF2m_simple_point2oct(const EC_GROUP *group, const EC_POINT *point,
                                point_conversion_form_t form,
                                unsigned char *buf, size_t len, BN_CTX *ctx)
{
    size_t ret;
    int used_ctx = 0;
    BIGNUM *x, *y, *yxi;
    size_t field_len, i, skip;
#ifndef FIPS_MODE
    BN_CTX *new_ctx = NULL;
#endif

    if ((form != POINT_CONVERSION_COMPRESSED)
        && (form != POINT_CONVERSION_UNCOMPRESSED)
        && (form != POINT_CONVERSION_HYBRID)) {
        ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, EC_R_INVALID_FORM);
        goto err;
    }

    if (EC_POINT_is_at_infinity(group, point)) {
        /* encodes to a single 0 octet */
        if (buf != NULL) {
            if (len < 1) {
                ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, EC_R_BUFFER_TOO_SMALL);
                return 0;
            }
            buf[0] = 0;
        }
        return 1;
    }

    /* ret := required output buffer length */
    field_len = (EC_GROUP_get_degree(group) + 7) / 8;
    ret =
        (form ==
         POINT_CONVERSION_COMPRESSED) ? 1 + field_len : 1 + 2 * field_len;

    /* if 'buf' is NULL, just return required length */
    if (buf != NULL) {
        if (len < ret) {
            ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, EC_R_BUFFER_TOO_SMALL);
            goto err;
        }

#ifndef FIPS_MODE
        if (ctx == NULL) {
            ctx = new_ctx = BN_CTX_new();
            if (ctx == NULL)
                return 0;
        }
#endif

        BN_CTX_start(ctx);
        used_ctx = 1;
        x = BN_CTX_get(ctx);
        y = BN_CTX_get(ctx);
        yxi = BN_CTX_get(ctx);
        if (yxi == NULL)
            goto err;

        if (!EC_POINT_get_affine_coordinates(group, point, x, y, ctx))
            goto err;

        buf[0] = form;
        if ((form != POINT_CONVERSION_UNCOMPRESSED) && !BN_is_zero(x)) {
            if (!group->meth->field_div(group, yxi, y, x, ctx))
                goto err;
            if (BN_is_odd(yxi))
                buf[0]++;
        }

        i = 1;

        skip = field_len - BN_num_bytes(x);
        if (skip > field_len) {
            ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, ERR_R_INTERNAL_ERROR);
            goto err;
        }
        while (skip > 0) {
            buf[i++] = 0;
            skip--;
        }
        skip = BN_bn2bin(x, buf + i);
        i += skip;
        if (i != 1 + field_len) {
            ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, ERR_R_INTERNAL_ERROR);
            goto err;
        }

        if (form == POINT_CONVERSION_UNCOMPRESSED
            || form == POINT_CONVERSION_HYBRID) {
            skip = field_len - BN_num_bytes(y);
            if (skip > field_len) {
                ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, ERR_R_INTERNAL_ERROR);
                goto err;
            }
            while (skip > 0) {
                buf[i++] = 0;
                skip--;
            }
            skip = BN_bn2bin(y, buf + i);
            i += skip;
        }

        if (i != ret) {
            ECerr(EC_F_EC_GF2M_SIMPLE_POINT2OCT, ERR_R_INTERNAL_ERROR);
            goto err;
        }
    }

    if (used_ctx)
        BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(new_ctx);
#endif
    return ret;

 err:
    if (used_ctx)
        BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(new_ctx);
#endif
    return 0;
}