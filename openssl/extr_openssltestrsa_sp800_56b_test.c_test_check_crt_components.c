#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* iqmp; struct TYPE_21__* dmq1; struct TYPE_21__* dmp1; struct TYPE_21__* n; } ;
typedef  TYPE_1__ RSA ;
typedef  TYPE_1__ BN_CTX ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (TYPE_1__*) ; 
 TYPE_1__* BN_CTX_new () ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 TYPE_1__* BN_new () ; 
 int /*<<< orphan*/  BN_set_word (TYPE_1__*,int const) ; 
 int /*<<< orphan*/  RSA_free (TYPE_1__*) ; 
 TYPE_1__* RSA_new () ; 
 int /*<<< orphan*/  RSA_set0_factors (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ TEST_BN_eq_word (TYPE_1__*,int const) ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (TYPE_1__*) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsa_check_crt_components (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  rsa_sp800_56b_derive_params_from_pq (TYPE_1__*,int,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static int test_check_crt_components(void)
{
    const int P = 15;
    const int Q = 17;
    const int E = 5;
    const int N = P*Q;
    const int DP = 3;
    const int DQ = 13;
    const int QINV = 8;

    int ret = 0;
    RSA *key = NULL;
    BN_CTX *ctx = NULL;
    BIGNUM *p = NULL, *q = NULL, *e = NULL;

    ret = TEST_ptr(key = RSA_new())
          && TEST_ptr(ctx = BN_CTX_new())
          && TEST_ptr(p = BN_new())
          && TEST_ptr(q = BN_new())
          && TEST_ptr(e = BN_new())
          && TEST_true(BN_set_word(p, P))
          && TEST_true(BN_set_word(q, Q))
          && TEST_true(BN_set_word(e, E))
          && TEST_true(RSA_set0_factors(key, p, q));
    if (!ret) {
        BN_free(p);
        BN_free(q);
        goto end;
    }
    ret = TEST_true(rsa_sp800_56b_derive_params_from_pq(key, 8, e, ctx))
          && TEST_BN_eq_word(key->n, N)
          && TEST_BN_eq_word(key->dmp1, DP)
          && TEST_BN_eq_word(key->dmq1, DQ)
          && TEST_BN_eq_word(key->iqmp, QINV)
          && TEST_true(rsa_check_crt_components(key, ctx))
          /* (a) 1 < dP < (p – 1). */
          && TEST_true(BN_set_word(key->dmp1, 1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmp1, P-1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmp1, DP))
          /* (b) 1 < dQ < (q - 1). */
          && TEST_true(BN_set_word(key->dmq1, 1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmq1, Q-1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmq1, DQ))
          /* (c) 1 < qInv < p */
          && TEST_true(BN_set_word(key->iqmp, 1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->iqmp, P))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->iqmp, QINV))
          /* (d) 1 = (dP . e) mod (p - 1)*/
          && TEST_true(BN_set_word(key->dmp1, DP+1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmp1, DP))
          /* (e) 1 = (dQ . e) mod (q - 1) */
          && TEST_true(BN_set_word(key->dmq1, DQ-1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->dmq1, DQ))
          /* (f) 1 = (qInv . q) mod p */
          && TEST_true(BN_set_word(key->iqmp, QINV+1))
          && TEST_false(rsa_check_crt_components(key, ctx))
          && TEST_true(BN_set_word(key->iqmp, QINV))
          /* check defaults are still valid */
          && TEST_true(rsa_check_crt_components(key, ctx));
end:
    BN_free(e);
    RSA_free(key);
    BN_CTX_free(ctx);
    return ret;
}