#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  felem_bytearray ;
typedef  int /*<<< orphan*/  felem ;
struct TYPE_15__ {TYPE_12__* generator; } ;
struct TYPE_14__ {int /*<<< orphan*/ ** g_pre_comp; } ;
struct TYPE_13__ {int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ NISTP521_PRE_COMP ;
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
 int /*<<< orphan*/  BN_bin2bn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_to_felem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EC_POINT_cmp (TYPE_2__*,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_2__*) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_nistp521_pre_comp_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_pre_comp_free (TYPE_2__*) ; 
 int /*<<< orphan*/  SETPRECOMP (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gmul ; 
 int /*<<< orphan*/  make_points_affine (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nistp521 ; 
 int /*<<< orphan*/ * nistp521_curve_params ; 
 TYPE_1__* nistp521_pre_comp_new () ; 
 int /*<<< orphan*/  point_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  point_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ec_GFp_nistp521_precompute_mult(EC_GROUP *group, BN_CTX *ctx)
{
    int ret = 0;
    NISTP521_PRE_COMP *pre = NULL;
    int i, j;
    BN_CTX *new_ctx = NULL;
    BIGNUM *x, *y;
    EC_POINT *generator = NULL;
    felem tmp_felems[16];

    /* throw away old precomputation */
    EC_pre_comp_free(group);
    if (ctx == NULL)
        if ((ctx = new_ctx = BN_CTX_new()) == NULL)
            return 0;
    BN_CTX_start(ctx);
    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (y == NULL)
        goto err;
    /* get the generator */
    if (group->generator == NULL)
        goto err;
    generator = EC_POINT_new(group);
    if (generator == NULL)
        goto err;
    BN_bin2bn(nistp521_curve_params[3], sizeof(felem_bytearray), x);
    BN_bin2bn(nistp521_curve_params[4], sizeof(felem_bytearray), y);
    if (!EC_POINT_set_affine_coordinates(group, generator, x, y, ctx))
        goto err;
    if ((pre = nistp521_pre_comp_new()) == NULL)
        goto err;
    /*
     * if the generator is the standard one, use built-in precomputation
     */
    if (0 == EC_POINT_cmp(group, generator, group->generator, ctx)) {
        memcpy(pre->g_pre_comp, gmul, sizeof(pre->g_pre_comp));
        goto done;
    }
    if ((!BN_to_felem(pre->g_pre_comp[1][0], group->generator->X)) ||
        (!BN_to_felem(pre->g_pre_comp[1][1], group->generator->Y)) ||
        (!BN_to_felem(pre->g_pre_comp[1][2], group->generator->Z)))
        goto err;
    /* compute 2^130*G, 2^260*G, 2^390*G */
    for (i = 1; i <= 4; i <<= 1) {
        point_double(pre->g_pre_comp[2 * i][0], pre->g_pre_comp[2 * i][1],
                     pre->g_pre_comp[2 * i][2], pre->g_pre_comp[i][0],
                     pre->g_pre_comp[i][1], pre->g_pre_comp[i][2]);
        for (j = 0; j < 129; ++j) {
            point_double(pre->g_pre_comp[2 * i][0],
                         pre->g_pre_comp[2 * i][1],
                         pre->g_pre_comp[2 * i][2],
                         pre->g_pre_comp[2 * i][0],
                         pre->g_pre_comp[2 * i][1],
                         pre->g_pre_comp[2 * i][2]);
        }
    }
    /* g_pre_comp[0] is the point at infinity */
    memset(pre->g_pre_comp[0], 0, sizeof(pre->g_pre_comp[0]));
    /* the remaining multiples */
    /* 2^130*G + 2^260*G */
    point_add(pre->g_pre_comp[6][0], pre->g_pre_comp[6][1],
              pre->g_pre_comp[6][2], pre->g_pre_comp[4][0],
              pre->g_pre_comp[4][1], pre->g_pre_comp[4][2],
              0, pre->g_pre_comp[2][0], pre->g_pre_comp[2][1],
              pre->g_pre_comp[2][2]);
    /* 2^130*G + 2^390*G */
    point_add(pre->g_pre_comp[10][0], pre->g_pre_comp[10][1],
              pre->g_pre_comp[10][2], pre->g_pre_comp[8][0],
              pre->g_pre_comp[8][1], pre->g_pre_comp[8][2],
              0, pre->g_pre_comp[2][0], pre->g_pre_comp[2][1],
              pre->g_pre_comp[2][2]);
    /* 2^260*G + 2^390*G */
    point_add(pre->g_pre_comp[12][0], pre->g_pre_comp[12][1],
              pre->g_pre_comp[12][2], pre->g_pre_comp[8][0],
              pre->g_pre_comp[8][1], pre->g_pre_comp[8][2],
              0, pre->g_pre_comp[4][0], pre->g_pre_comp[4][1],
              pre->g_pre_comp[4][2]);
    /* 2^130*G + 2^260*G + 2^390*G */
    point_add(pre->g_pre_comp[14][0], pre->g_pre_comp[14][1],
              pre->g_pre_comp[14][2], pre->g_pre_comp[12][0],
              pre->g_pre_comp[12][1], pre->g_pre_comp[12][2],
              0, pre->g_pre_comp[2][0], pre->g_pre_comp[2][1],
              pre->g_pre_comp[2][2]);
    for (i = 1; i < 8; ++i) {
        /* odd multiples: add G */
        point_add(pre->g_pre_comp[2 * i + 1][0],
                  pre->g_pre_comp[2 * i + 1][1],
                  pre->g_pre_comp[2 * i + 1][2], pre->g_pre_comp[2 * i][0],
                  pre->g_pre_comp[2 * i][1], pre->g_pre_comp[2 * i][2], 0,
                  pre->g_pre_comp[1][0], pre->g_pre_comp[1][1],
                  pre->g_pre_comp[1][2]);
    }
    make_points_affine(15, &(pre->g_pre_comp[1]), tmp_felems);

 done:
    SETPRECOMP(group, nistp521, pre);
    ret = 1;
    pre = NULL;
 err:
    BN_CTX_end(ctx);
    EC_POINT_free(generator);
    BN_CTX_free(new_ctx);
    EC_nistp521_pre_comp_free(pre);
    return ret;
}