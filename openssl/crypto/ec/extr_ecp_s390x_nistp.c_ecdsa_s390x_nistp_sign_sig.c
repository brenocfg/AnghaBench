#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  param ;
struct TYPE_5__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_1__ ECDSA_SIG ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int BN_bn2binpad (int /*<<< orphan*/  const*,unsigned char*,int) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/  const*) ; 
 void* BN_new () ; 
 int /*<<< orphan*/  const* BN_secure_new () ; 
 int /*<<< orphan*/  ECDSA_SIG_free (TYPE_1__*) ; 
 TYPE_1__* ECDSA_SIG_new () ; 
 int /*<<< orphan*/  EC_F_ECDSA_S390X_NISTP_SIGN_SIG ; 
 int /*<<< orphan*/  EC_KEY_can_sign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_KEY_get0_private_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING ; 
 int /*<<< orphan*/  EC_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  EC_R_RANDOM_NUMBER_GENERATION_FAILED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_ECDSA_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int RAND_priv_bytes (unsigned char*,int) ; 
 unsigned int S390X_KDSA_D ; 
 int S390X_OFF_H (int) ; 
 int S390X_OFF_K (int) ; 
 int S390X_OFF_R (int) ; 
 int S390X_OFF_RN (int) ; 
 int S390X_OFF_S (int) ; 
 int S390X_SIZE_PARAM ; 
 scalar_t__ ec_group_do_inverse_ord (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ s390x_kdsa (unsigned int,unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ECDSA_SIG *ecdsa_s390x_nistp_sign_sig(const unsigned char *dgst,
                                             int dgstlen,
                                             const BIGNUM *kinv,
                                             const BIGNUM *r,
                                             EC_KEY *eckey,
                                             unsigned int fc, int len)
{
    unsigned char param[S390X_SIZE_PARAM];
    int ok = 0;
    BIGNUM *k;
    ECDSA_SIG *sig;
    const EC_GROUP *group;
    const BIGNUM *privkey;
    int off;

    group = EC_KEY_get0_group(eckey);
    privkey = EC_KEY_get0_private_key(eckey);
    if (group == NULL || privkey == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, EC_R_MISSING_PARAMETERS);
        return NULL;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG,
              EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return NULL;
    }

    k = BN_secure_new();
    sig = ECDSA_SIG_new();
    if (k == NULL || sig == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_MALLOC_FAILURE);
        goto ret;
    }

    sig->r = BN_new();
    sig->s = BN_new();
    if (sig->r == NULL || sig->s == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_MALLOC_FAILURE);
        goto ret;
    }

    memset(param, 0, sizeof(param));
    off = len - (dgstlen > len ? len : dgstlen);
    memcpy(param + S390X_OFF_H(len) + off, dgst, len - off);

    if (BN_bn2binpad(privkey, param + S390X_OFF_K(len), len) == -1) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_BN_LIB);
        goto ret;
    }

    if (r == NULL || kinv == NULL) {
        /*
         * Generate random k and copy to param param block. RAND_priv_bytes
         * is used instead of BN_priv_rand_range or BN_generate_dsa_nonce
         * because kdsa instruction constructs an in-range, invertible nonce
         * internally implementing counter-measures for RNG weakness.
         */
         if (RAND_priv_bytes(param + S390X_OFF_RN(len), len) != 1) {
             ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG,
                   EC_R_RANDOM_NUMBER_GENERATION_FAILED);
             goto ret;
         }
    } else {
        /* Reconstruct k = (k^-1)^-1. */
        if (ec_group_do_inverse_ord(group, k, kinv, NULL) == 0
            || BN_bn2binpad(k, param + S390X_OFF_RN(len), len) == -1) {
            ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_BN_LIB);
            goto ret;
        }
        /* Turns KDSA internal nonce-generation off. */
        fc |= S390X_KDSA_D;
    }

    if (s390x_kdsa(fc, param, NULL, 0) != 0) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_ECDSA_LIB);
        goto ret;
    }

    if (BN_bin2bn(param + S390X_OFF_R(len), len, sig->r) == NULL
        || BN_bin2bn(param + S390X_OFF_S(len), len, sig->s) == NULL) {
        ECerr(EC_F_ECDSA_S390X_NISTP_SIGN_SIG, ERR_R_BN_LIB);
        goto ret;
    }

    ok = 1;
ret:
    OPENSSL_cleanse(param + S390X_OFF_K(len), 2 * len);
    if (ok != 1) {
        ECDSA_SIG_free(sig);
        sig = NULL;
    }
    BN_clear_free(k);
    return sig;
}