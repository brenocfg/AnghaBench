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
typedef  unsigned char DH ;
typedef  unsigned char BN_GENCB ;
typedef  unsigned char BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GENCB_free (unsigned char*) ; 
 unsigned char* BN_GENCB_new () ; 
 int /*<<< orphan*/  BN_GENCB_set (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* BN_dup (unsigned char const*) ; 
 int /*<<< orphan*/  BN_free (unsigned char*) ; 
 unsigned char* BN_new () ; 
 int BN_set_word (unsigned char*,long) ; 
 int DH_CHECK_INVALID_J_VALUE ; 
 int DH_CHECK_INVALID_Q_VALUE ; 
 int DH_CHECK_P_NOT_PRIME ; 
 int DH_CHECK_P_NOT_SAFE_PRIME ; 
 int DH_CHECK_Q_NOT_PRIME ; 
 int /*<<< orphan*/  DH_GENERATOR_5 ; 
 int DH_MODULUS_TOO_LARGE ; 
 int DH_MODULUS_TOO_SMALL ; 
 int DH_NOT_SUITABLE_GENERATOR ; 
 int DH_UNABLE_TO_CHECK_GENERATOR ; 
 int /*<<< orphan*/  DH_check (unsigned char*,int*) ; 
 int DH_compute_key (unsigned char*,unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  DH_free (unsigned char*) ; 
 int DH_generate_key (unsigned char*) ; 
 int DH_generate_parameters_ex (unsigned char*,int,int /*<<< orphan*/ ,unsigned char*) ; 
 unsigned char const* DH_get0_g (unsigned char*) ; 
 int /*<<< orphan*/  DH_get0_key (unsigned char*,unsigned char const**,unsigned char const**) ; 
 unsigned char const* DH_get0_p (unsigned char*) ; 
 int /*<<< orphan*/  DH_get0_pqg (unsigned char*,unsigned char const**,unsigned char const**,unsigned char const**) ; 
 unsigned char const* DH_get0_priv_key (unsigned char*) ; 
 unsigned char const* DH_get0_pub_key (unsigned char*) ; 
 unsigned char const* DH_get0_q (unsigned char*) ; 
 unsigned char* DH_new () ; 
 int DH_set0_key (unsigned char*,int /*<<< orphan*/ *,unsigned char*) ; 
 int DH_set0_pqg (unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int DH_size (unsigned char*) ; 
 unsigned char* DHparams_dup (unsigned char*) ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  TEST_false (int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 int /*<<< orphan*/  cb ; 

__attribute__((used)) static int dh_test(void)
{
    DH *dh = NULL;
    BIGNUM *p = NULL, *q = NULL, *g = NULL;
    const BIGNUM *p2, *q2, *g2;
    BIGNUM *priv_key = NULL;
    const BIGNUM *pub_key2, *priv_key2;
    BN_GENCB *_cb = NULL;
    DH *a = NULL;
    DH *b = NULL;
    DH *c = NULL;
    const BIGNUM *ap = NULL, *ag = NULL, *apub_key = NULL;
    const BIGNUM *bpub_key = NULL, *bpriv_key = NULL;
    BIGNUM *bp = NULL, *bg = NULL, *cpriv_key = NULL;
    unsigned char *abuf = NULL;
    unsigned char *bbuf = NULL;
    unsigned char *cbuf = NULL;
    int i, alen, blen, clen, aout, bout, cout;
    int ret = 0;

    if (!TEST_ptr(dh = DH_new())
        || !TEST_ptr(p = BN_new())
        || !TEST_ptr(q = BN_new())
        || !TEST_ptr(g = BN_new())
        || !TEST_ptr(priv_key = BN_new()))
        goto err1;

    /*
     * I) basic tests
     */

    /* using a small predefined Sophie Germain DH group with generator 3 */
    if (!TEST_true(BN_set_word(p, 4079L))
        || !TEST_true(BN_set_word(q, 2039L))
        || !TEST_true(BN_set_word(g, 3L))
        || !TEST_true(DH_set0_pqg(dh, p, q, g)))
        goto err1;

    /* check fails, because p is way too small */
    if (!DH_check(dh, &i))
        goto err2;
    i ^= DH_MODULUS_TOO_SMALL;
    if (!TEST_false(i & DH_CHECK_P_NOT_PRIME)
            || !TEST_false(i & DH_CHECK_P_NOT_SAFE_PRIME)
            || !TEST_false(i & DH_UNABLE_TO_CHECK_GENERATOR)
            || !TEST_false(i & DH_NOT_SUITABLE_GENERATOR)
            || !TEST_false(i & DH_CHECK_Q_NOT_PRIME)
            || !TEST_false(i & DH_CHECK_INVALID_Q_VALUE)
            || !TEST_false(i & DH_CHECK_INVALID_J_VALUE)
            || !TEST_false(i & DH_MODULUS_TOO_SMALL)
            || !TEST_false(i & DH_MODULUS_TOO_LARGE)
            || !TEST_false(i))
        goto err2;

    /* test the combined getter for p, q, and g */
    DH_get0_pqg(dh, &p2, &q2, &g2);
    if (!TEST_ptr_eq(p2, p)
        || !TEST_ptr_eq(q2, q)
        || !TEST_ptr_eq(g2, g))
        goto err2;

    /* test the simple getters for p, q, and g */
    if (!TEST_ptr_eq(DH_get0_p(dh), p2)
        || !TEST_ptr_eq(DH_get0_q(dh), q2)
        || !TEST_ptr_eq(DH_get0_g(dh), g2))
        goto err2;

    /* set the private key only*/
    if (!TEST_true(BN_set_word(priv_key, 1234L))
        || !TEST_true(DH_set0_key(dh, NULL, priv_key)))
        goto err2;

    /* test the combined getter for pub_key and priv_key */
    DH_get0_key(dh, &pub_key2, &priv_key2);
    if (!TEST_ptr_eq(pub_key2, NULL)
        || !TEST_ptr_eq(priv_key2, priv_key))
        goto err3;

    /* test the simple getters for pub_key and priv_key */
    if (!TEST_ptr_eq(DH_get0_pub_key(dh), pub_key2)
        || !TEST_ptr_eq(DH_get0_priv_key(dh), priv_key2))
        goto err3;

    /* now generate a key pair (expect failure since modulus is too small) */
    if (!TEST_false(DH_generate_key(dh)))
        goto err3;

    /* We'll have a stale error on the queue from the above test so clear it */
    ERR_clear_error();

    /*
     * II) key generation
     */

    /* generate a DH group ... */
    if (!TEST_ptr(_cb = BN_GENCB_new()))
        goto err3;
    BN_GENCB_set(_cb, &cb, NULL);
    if (!TEST_ptr(a = DH_new())
            || !TEST_true(DH_generate_parameters_ex(a, 512,
                                                    DH_GENERATOR_5, _cb)))
        goto err3;

    /* ... and check whether it is valid */
    if (!DH_check(a, &i))
        goto err3;
    if (!TEST_false(i & DH_CHECK_P_NOT_PRIME)
            || !TEST_false(i & DH_CHECK_P_NOT_SAFE_PRIME)
            || !TEST_false(i & DH_UNABLE_TO_CHECK_GENERATOR)
            || !TEST_false(i & DH_NOT_SUITABLE_GENERATOR)
            || !TEST_false(i & DH_CHECK_Q_NOT_PRIME)
            || !TEST_false(i & DH_CHECK_INVALID_Q_VALUE)
            || !TEST_false(i & DH_CHECK_INVALID_J_VALUE)
            || !TEST_false(i & DH_MODULUS_TOO_SMALL)
            || !TEST_false(i & DH_MODULUS_TOO_LARGE)
            || !TEST_false(i))
        goto err3;

    DH_get0_pqg(a, &ap, NULL, &ag);

    /* now create another copy of the DH group for the peer */
    if (!TEST_ptr(b = DH_new()))
        goto err3;

    if (!TEST_ptr(bp = BN_dup(ap))
            || !TEST_ptr(bg = BN_dup(ag))
            || !TEST_true(DH_set0_pqg(b, bp, NULL, bg)))
        goto err3;
    bp = bg = NULL;

    /*
     * III) simulate a key exchange
     */

    if (!DH_generate_key(a))
        goto err3;
    DH_get0_key(a, &apub_key, NULL);

    if (!DH_generate_key(b))
        goto err3;
    DH_get0_key(b, &bpub_key, &bpriv_key);

    /* Also test with a private-key-only copy of |b|. */
    if (!TEST_ptr(c = DHparams_dup(b))
            || !TEST_ptr(cpriv_key = BN_dup(bpriv_key))
            || !TEST_true(DH_set0_key(c, NULL, cpriv_key)))
        goto err3;
    cpriv_key = NULL;

    alen = DH_size(a);
    if (!TEST_ptr(abuf = OPENSSL_malloc(alen))
            || !TEST_true((aout = DH_compute_key(abuf, bpub_key, a)) != -1))
        goto err3;

    blen = DH_size(b);
    if (!TEST_ptr(bbuf = OPENSSL_malloc(blen))
            || !TEST_true((bout = DH_compute_key(bbuf, apub_key, b)) != -1))
        goto err3;

    clen = DH_size(c);
    if (!TEST_ptr(cbuf = OPENSSL_malloc(clen))
            || !TEST_true((cout = DH_compute_key(cbuf, apub_key, c)) != -1))
        goto err3;

    if (!TEST_true(aout >= 20)
            || !TEST_mem_eq(abuf, aout, bbuf, bout)
            || !TEST_mem_eq(abuf, aout, cbuf, cout))
        goto err3;

    ret = 1;
    goto success;

 err1:
    /* an error occurred before p,q,g were assigned to dh */
    BN_free(p);
    BN_free(q);
    BN_free(g);
 err2:
    /* an error occurred before priv_key was assigned to dh */
    BN_free(priv_key);
 err3:
 success:
    OPENSSL_free(abuf);
    OPENSSL_free(bbuf);
    OPENSSL_free(cbuf);
    DH_free(b);
    DH_free(a);
    DH_free(c);
    BN_free(bp);
    BN_free(bg);
    BN_free(cpriv_key);
    BN_GENCB_free(_cb);
    DH_free(dh);

    return ret;
}