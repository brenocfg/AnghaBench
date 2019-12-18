#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__* seed; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
typedef  TYPE_1__ X9_62_CURVE ;
struct TYPE_12__ {int flags; } ;
struct TYPE_11__ {scalar_t__ seed_len; scalar_t__ seed; } ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_free (TYPE_7__*) ; 
 TYPE_7__* ASN1_BIT_STRING_new () ; 
 int /*<<< orphan*/  ASN1_BIT_STRING_set (TYPE_7__*,scalar_t__,int) ; 
 int /*<<< orphan*/  ASN1_OCTET_STRING_set (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 scalar_t__ BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  EC_F_EC_ASN1_GROUP2CURVE ; 
 int /*<<< orphan*/  EC_GROUP_get_curve (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_GROUP_get_degree (TYPE_2__ const*) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_ASN1_LIB ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 

__attribute__((used)) static int ec_asn1_group2curve(const EC_GROUP *group, X9_62_CURVE *curve)
{
    int ok = 0;
    BIGNUM *tmp_1 = NULL, *tmp_2 = NULL;
    unsigned char *a_buf = NULL, *b_buf = NULL;
    size_t len;

    if (!group || !curve || !curve->a || !curve->b)
        return 0;

    if ((tmp_1 = BN_new()) == NULL || (tmp_2 = BN_new()) == NULL) {
        ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* get a and b */
    if (!EC_GROUP_get_curve(group, NULL, tmp_1, tmp_2, NULL)) {
        ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_EC_LIB);
        goto err;
    }

    /*
     * Per SEC 1, the curve coefficients must be padded up to size. See C.2's
     * definition of Curve, C.1's definition of FieldElement, and 2.3.5's
     * definition of how to encode the field elements.
     */
    len = ((size_t)EC_GROUP_get_degree(group) + 7) / 8;
    if ((a_buf = OPENSSL_malloc(len)) == NULL
        || (b_buf = OPENSSL_malloc(len)) == NULL) {
        ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (BN_bn2binpad(tmp_1, a_buf, len) < 0
        || BN_bn2binpad(tmp_2, b_buf, len) < 0) {
        ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_BN_LIB);
        goto err;
    }

    /* set a and b */
    if (!ASN1_OCTET_STRING_set(curve->a, a_buf, len)
        || !ASN1_OCTET_STRING_set(curve->b, b_buf, len)) {
        ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_ASN1_LIB);
        goto err;
    }

    /* set the seed (optional) */
    if (group->seed) {
        if (!curve->seed)
            if ((curve->seed = ASN1_BIT_STRING_new()) == NULL) {
                ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_MALLOC_FAILURE);
                goto err;
            }
        curve->seed->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
        curve->seed->flags |= ASN1_STRING_FLAG_BITS_LEFT;
        if (!ASN1_BIT_STRING_set(curve->seed, group->seed,
                                 (int)group->seed_len)) {
            ECerr(EC_F_EC_ASN1_GROUP2CURVE, ERR_R_ASN1_LIB);
            goto err;
        }
    } else {
        ASN1_BIT_STRING_free(curve->seed);
        curve->seed = NULL;
    }

    ok = 1;

 err:
    OPENSSL_free(a_buf);
    OPENSSL_free(b_buf);
    BN_free(tmp_1);
    BN_free(tmp_2);
    return ok;
}