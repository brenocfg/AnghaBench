#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tbs ;
struct TYPE_2__ {int nid; } ;
typedef  unsigned char EVP_PKEY ;
typedef  unsigned char EVP_MD_CTX ;
typedef  unsigned char EC_KEY ;

/* Variables and functions */
 int ECDSA_size (unsigned char*) ; 
 int /*<<< orphan*/  EC_KEY_generate_key (unsigned char*) ; 
 unsigned char* EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  EVP_DigestSign (unsigned char*,unsigned char*,size_t*,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestSignInit (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  EVP_DigestVerify (unsigned char*,unsigned char*,size_t,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (unsigned char*) ; 
 unsigned char* EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_reset (unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (unsigned char*) ; 
 unsigned char* EVP_PKEY_new () ; 
 int NID_ipsec3 ; 
 int NID_ipsec4 ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  RAND_bytes (unsigned char*,int) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_ge (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (size_t,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int test_builtin(int n)
{
    EC_KEY *eckey_neg = NULL, *eckey = NULL;
    unsigned char dirt, offset, tbs[128];
    unsigned char *sig = NULL;
    EVP_PKEY *pkey_neg = NULL, *pkey = NULL;
    EVP_MD_CTX *mctx = NULL;
    size_t sig_len;
    int nid, ret = 0;
    int temp;

    nid = curves[n].nid;

    /* skip built-in curves where ord(G) is not prime */
    if (nid == NID_ipsec4 || nid == NID_ipsec3) {
        TEST_info("skipped: ECDSA unsupported for curve %s", OBJ_nid2sn(nid));
        return 1;
    }

    TEST_info("testing ECDSA for curve %s", OBJ_nid2sn(nid));

    if (!TEST_ptr(mctx = EVP_MD_CTX_new())
        /* get some random message data */
        || !TEST_true(RAND_bytes(tbs, sizeof(tbs)))
        /* real key */
        || !TEST_ptr(eckey = EC_KEY_new_by_curve_name(nid))
        || !TEST_true(EC_KEY_generate_key(eckey))
        || !TEST_ptr(pkey = EVP_PKEY_new())
        || !TEST_true(EVP_PKEY_assign_EC_KEY(pkey, eckey))
        /* fake key for negative testing */
        || !TEST_ptr(eckey_neg = EC_KEY_new_by_curve_name(nid))
        || !TEST_true(EC_KEY_generate_key(eckey_neg))
        || !TEST_ptr(pkey_neg = EVP_PKEY_new())
        || !TEST_true(EVP_PKEY_assign_EC_KEY(pkey_neg, eckey_neg)))
        goto err;

    temp = ECDSA_size(eckey);

    if (!TEST_int_ge(temp, 0)
        || !TEST_ptr(sig = OPENSSL_malloc(sig_len = (size_t)temp))
        /* create a signature */
        || !TEST_true(EVP_DigestSignInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_true(EVP_DigestSign(mctx, sig, &sig_len, tbs, sizeof(tbs)))
        || !TEST_int_le(sig_len, ECDSA_size(eckey))
        /* negative test, verify with wrong key, 0 return */
        || !TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey_neg))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 0)
        /* negative test, verify with wrong signature length, -1 return */
        || !TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len - 1, tbs, sizeof(tbs)), -1)
        /* positive test, verify with correct key, 1 return */
        || !TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 1))
        goto err;

    /* muck with the message, test it fails with 0 return */
    tbs[0] ^= 1;
    if (!TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 0))
        goto err;
    /* un-muck and test it verifies */
    tbs[0] ^= 1;
    if (!TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 1))
        goto err;

    /*-
     * Muck with the ECDSA signature. The DER encoding is one of:
     * - 30 LL 02 ..
     * - 30 81 LL 02 ..
     *
     * - Sometimes this mucks with the high level DER sequence wrapper:
     *   in that case, DER-parsing of the whole signature should fail.
     *
     * - Sometimes this mucks with the DER-encoding of ECDSA.r:
     *   in that case, DER-parsing of ECDSA.r should fail.
     *
     * - Sometimes this mucks with the DER-encoding of ECDSA.s:
     *   in that case, DER-parsing of ECDSA.s should fail.
     *
     * - Sometimes this mucks with ECDSA.r:
     *   in that case, the signature verification should fail.
     *
     * - Sometimes this mucks with ECDSA.s:
     *   in that case, the signature verification should fail.
     *
     * The usual case is changing the integer value of ECDSA.r or ECDSA.s.
     * Because the ratio of DER overhead to signature bytes is small.
     * So most of the time it will be one of the last two cases.
     *
     * In any case, EVP_PKEY_verify should not return 1 for valid.
     */
    offset = tbs[0] % sig_len;
    dirt = tbs[1] ? tbs[1] : 1;
    sig[offset] ^= dirt;
    if (!TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_ne(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 1))
        goto err;
    /* un-muck and test it verifies */
    sig[offset] ^= dirt;
    if (!TEST_true(EVP_MD_CTX_reset(mctx))
        || !TEST_true(EVP_DigestVerifyInit(mctx, NULL, NULL, NULL, pkey))
        || !TEST_int_eq(EVP_DigestVerify(mctx, sig, sig_len, tbs, sizeof(tbs)), 1))
        goto err;

    ret = 1;
 err:
    EVP_PKEY_free(pkey);
    EVP_PKEY_free(pkey_neg);
    EVP_MD_CTX_free(mctx);
    OPENSSL_free(sig);
    return ret;
}