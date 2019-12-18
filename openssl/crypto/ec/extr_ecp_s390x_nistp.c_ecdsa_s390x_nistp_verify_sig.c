#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  param ;
struct TYPE_9__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
struct TYPE_8__ {TYPE_1__* meth; int /*<<< orphan*/  libctx; } ;
struct TYPE_7__ {int (* point_get_affine_coordinates ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  TYPE_2__ EC_GROUP ;
typedef  TYPE_3__ ECDSA_SIG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int BN_bn2binpad (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EC_F_ECDSA_S390X_NISTP_VERIFY_SIG ; 
 int /*<<< orphan*/  EC_KEY_can_sign (int /*<<< orphan*/ *) ; 
 TYPE_2__* EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING ; 
 int /*<<< orphan*/  EC_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int S390X_OFF_H (int) ; 
 int S390X_OFF_R (int) ; 
 int S390X_OFF_S (int) ; 
 int S390X_OFF_X (int) ; 
 int S390X_OFF_Y (int) ; 
 int S390X_SIZE_PARAM ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ s390x_kdsa (unsigned int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecdsa_s390x_nistp_verify_sig(const unsigned char *dgst, int dgstlen,
                                        const ECDSA_SIG *sig, EC_KEY *eckey,
                                        unsigned int fc, int len)
{
    unsigned char param[S390X_SIZE_PARAM];
    int rc = -1;
    BN_CTX *ctx;
    BIGNUM *x, *y;
    const EC_GROUP *group;
    const EC_POINT *pubkey;
    int off;

    group = EC_KEY_get0_group(eckey);
    pubkey = EC_KEY_get0_public_key(eckey);
    if (eckey == NULL || group == NULL || pubkey == NULL || sig == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_VERIFY_SIG, EC_R_MISSING_PARAMETERS);
        return -1;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_S390X_NISTP_VERIFY_SIG,
              EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return -1;
    }

    ctx = BN_CTX_new_ex(group->libctx);
    if (ctx == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_VERIFY_SIG, ERR_R_MALLOC_FAILURE);
        return -1;
    }

    BN_CTX_start(ctx);

    x = BN_CTX_get(ctx);
    y = BN_CTX_get(ctx);
    if (x == NULL || y == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_VERIFY_SIG, ERR_R_MALLOC_FAILURE);
        goto ret;
    }

    memset(param, 0, sizeof(param));
    off = len - (dgstlen > len ? len : dgstlen);
    memcpy(param + S390X_OFF_H(len) + off, dgst, len - off);

    if (group->meth->point_get_affine_coordinates(group, pubkey,
                                                  x, y, ctx) != 1
        || BN_bn2binpad(sig->r, param + S390X_OFF_R(len), len) == -1
        || BN_bn2binpad(sig->s, param + S390X_OFF_S(len), len) == -1
        || BN_bn2binpad(x, param + S390X_OFF_X(len), len) == -1
        || BN_bn2binpad(y, param + S390X_OFF_Y(len), len) == -1) {
        ECerr(EC_F_ECDSA_S390X_NISTP_VERIFY_SIG, ERR_R_BN_LIB);
        goto ret;
    }

    rc = s390x_kdsa(fc, param, NULL, 0) == 0 ? 1 : 0;
ret:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return rc;
}