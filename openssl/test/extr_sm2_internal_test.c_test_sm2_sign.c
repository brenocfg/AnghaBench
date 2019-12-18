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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  ECDSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECDSA_SIG_get0 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new () ; 
 int EC_KEY_set_group (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EC_KEY_set_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EC_KEY_set_public_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_sm3 () ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  fake_rand_bytes_offset ; 
 int /*<<< orphan*/  fake_rand_size ; 
 int /*<<< orphan*/  restore_rand () ; 
 int /*<<< orphan*/ * sm2_do_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t const) ; 
 int sm2_do_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t const) ; 
 int /*<<< orphan*/  start_fake_rand (char const*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int test_sm2_sign(const EC_GROUP *group,
                         const char *userid,
                         const char *privkey_hex,
                         const char *message,
                         const char *k_hex,
                         const char *r_hex,
                         const char *s_hex)
{
    const size_t msg_len = strlen(message);
    int ok = 0;
    BIGNUM *priv = NULL;
    EC_POINT *pt = NULL;
    EC_KEY *key = NULL;
    ECDSA_SIG *sig = NULL;
    const BIGNUM *sig_r = NULL;
    const BIGNUM *sig_s = NULL;
    BIGNUM *r = NULL;
    BIGNUM *s = NULL;

    if (!TEST_true(BN_hex2bn(&priv, privkey_hex)))
        goto done;

    key = EC_KEY_new();
    if (!TEST_ptr(key)
            || !TEST_true(EC_KEY_set_group(key, group))
            || !TEST_true(EC_KEY_set_private_key(key, priv)))
        goto done;

    pt = EC_POINT_new(group);
    if (!TEST_ptr(pt)
            || !TEST_true(EC_POINT_mul(group, pt, priv, NULL, NULL, NULL))
            || !TEST_true(EC_KEY_set_public_key(key, pt)))
        goto done;

    start_fake_rand(k_hex);
    sig = sm2_do_sign(key, EVP_sm3(), (const uint8_t *)userid, strlen(userid),
                      (const uint8_t *)message, msg_len);
    if (!TEST_ptr(sig)
            || !TEST_size_t_eq(fake_rand_bytes_offset, fake_rand_size)) {
        restore_rand();
        goto done;
    }
    restore_rand();

    ECDSA_SIG_get0(sig, &sig_r, &sig_s);

    if (!TEST_true(BN_hex2bn(&r, r_hex))
            || !TEST_true(BN_hex2bn(&s, s_hex))
            || !TEST_BN_eq(r, sig_r)
            || !TEST_BN_eq(s, sig_s))
        goto done;

    ok = sm2_do_verify(key, EVP_sm3(), sig, (const uint8_t *)userid,
                       strlen(userid), (const uint8_t *)message, msg_len);

    /* We goto done whether this passes or fails */
    TEST_true(ok);

 done:
    ECDSA_SIG_free(sig);
    EC_POINT_free(pt);
    EC_KEY_free(key);
    BN_free(priv);
    BN_free(r);
    BN_free(s);

    return ok;
}