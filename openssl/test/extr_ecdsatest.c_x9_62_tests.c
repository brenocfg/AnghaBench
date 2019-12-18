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
struct TYPE_2__ {int nid; int md_nid; char* r; char* s; char* msg; char const* Q; int /*<<< orphan*/  k; int /*<<< orphan*/  d; } ;
typedef  unsigned char EVP_MD_CTX ;
typedef  unsigned char EC_KEY ;
typedef  unsigned char ECDSA_SIG ;
typedef  unsigned char BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (unsigned char*) ; 
 int /*<<< orphan*/  BN_free (unsigned char*) ; 
 size_t BN_hex2bn (unsigned char**,char const*) ; 
 unsigned char* BN_new () ; 
 int /*<<< orphan*/  ECDSA_SIG_free (unsigned char*) ; 
 int /*<<< orphan*/  ECDSA_SIG_get0 (unsigned char*,unsigned char const**,unsigned char const**) ; 
 unsigned char* ECDSA_do_sign_ex (unsigned char*,unsigned int,unsigned char*,unsigned char*,unsigned char*) ; 
 long ECDSA_do_verify (unsigned char*,unsigned int,unsigned char*,unsigned char*) ; 
 size_t ECDSA_sign_setup (unsigned char*,int /*<<< orphan*/ *,unsigned char**,unsigned char**) ; 
 int /*<<< orphan*/  EC_KEY_free (unsigned char*) ; 
 size_t EC_KEY_generate_key (unsigned char*) ; 
 size_t EC_KEY_key2buf (unsigned char*,int /*<<< orphan*/ ,unsigned char**,int /*<<< orphan*/ *) ; 
 unsigned char* EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/ * EC_curve_nid2nist (int) ; 
 size_t EVP_DigestFinal_ex (unsigned char*,unsigned char*,unsigned int*) ; 
 size_t EVP_DigestInit_ex (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t EVP_DigestUpdate (unsigned char*,unsigned char*,long) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (unsigned char*) ; 
 unsigned char* EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_get_digestbynid (int) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_hexstr2buf (char const*,long*) ; 
 int /*<<< orphan*/  POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  TEST_BN_eq (unsigned char const*,unsigned char*) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (long,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,long,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int TEST_skip (char*) ; 
 int /*<<< orphan*/  TEST_true (size_t) ; 
 size_t change_rand () ; 
 TYPE_1__* ecdsa_cavs_kats ; 
 int /*<<< orphan*/ * numbers ; 
 size_t restore_rand () ; 
 int use_fake ; 

__attribute__((used)) static int x9_62_tests(int n)
{
    int nid, md_nid, ret = 0;
    const char *r_in = NULL, *s_in = NULL, *tbs = NULL;
    unsigned char *pbuf = NULL, *qbuf = NULL, *message = NULL;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int dgst_len = 0;
    long q_len, msg_len = 0;
    size_t p_len;
    EVP_MD_CTX *mctx = NULL;
    EC_KEY *key = NULL;
    ECDSA_SIG *signature = NULL;
    BIGNUM *r = NULL, *s = NULL;
    BIGNUM *kinv = NULL, *rp = NULL;
    const BIGNUM *sig_r = NULL, *sig_s = NULL;

    nid = ecdsa_cavs_kats[n].nid;
    md_nid = ecdsa_cavs_kats[n].md_nid;
    r_in = ecdsa_cavs_kats[n].r;
    s_in = ecdsa_cavs_kats[n].s;
    tbs = ecdsa_cavs_kats[n].msg;
    numbers[0] = ecdsa_cavs_kats[n].d;
    numbers[1] = ecdsa_cavs_kats[n].k;

    TEST_info("ECDSA KATs for curve %s", OBJ_nid2sn(nid));

#ifdef FIPS_MODE
    if (EC_curve_nid2nist(nid) == NULL)
        return TEST_skip("skip non approved curves");
#endif /* FIPS_MODE */

    if (!TEST_ptr(mctx = EVP_MD_CTX_new())
        /* get the message digest */
        || !TEST_ptr(message = OPENSSL_hexstr2buf(tbs, &msg_len))
        || !TEST_true(EVP_DigestInit_ex(mctx, EVP_get_digestbynid(md_nid), NULL))
        || !TEST_true(EVP_DigestUpdate(mctx, message, msg_len))
        || !TEST_true(EVP_DigestFinal_ex(mctx, digest, &dgst_len))
        /* create the key */
        || !TEST_ptr(key = EC_KEY_new_by_curve_name(nid))
        /* load KAT variables */
        || !TEST_ptr(r = BN_new())
        || !TEST_ptr(s = BN_new())
        || !TEST_true(BN_hex2bn(&r, r_in))
        || !TEST_true(BN_hex2bn(&s, s_in))
        /* swap the RNG source */
        || !TEST_true(change_rand()))
        goto err;

    /* public key must match KAT */
    use_fake = 1;
    if (!TEST_true(EC_KEY_generate_key(key))
        || !TEST_true(p_len = EC_KEY_key2buf(key, POINT_CONVERSION_UNCOMPRESSED,
                                             &pbuf, NULL))
        || !TEST_ptr(qbuf = OPENSSL_hexstr2buf(ecdsa_cavs_kats[n].Q, &q_len))
        || !TEST_int_eq(q_len, p_len)
        || !TEST_mem_eq(qbuf, q_len, pbuf, p_len))
        goto err;

    /* create the signature via ECDSA_sign_setup to avoid use of ECDSA nonces */
    use_fake = 1;
    if (!TEST_true(ECDSA_sign_setup(key, NULL, &kinv, &rp))
        || !TEST_ptr(signature = ECDSA_do_sign_ex(digest, dgst_len,
                                                  kinv, rp, key))
        /* verify the signature */
        || !TEST_int_eq(ECDSA_do_verify(digest, dgst_len, signature, key), 1))
        goto err;

    /* compare the created signature with the expected signature */
    ECDSA_SIG_get0(signature, &sig_r, &sig_s);
    if (!TEST_BN_eq(sig_r, r)
        || !TEST_BN_eq(sig_s, s))
        goto err;

    ret = 1;

 err:
    /* restore the RNG source */
    if (!TEST_true(restore_rand()))
        ret = 0;

    OPENSSL_free(message);
    OPENSSL_free(pbuf);
    OPENSSL_free(qbuf);
    EC_KEY_free(key);
    ECDSA_SIG_free(signature);
    BN_free(r);
    BN_free(s);
    EVP_MD_CTX_free(mctx);
    BN_clear_free(kinv);
    BN_clear_free(rp);
    return ret;
}