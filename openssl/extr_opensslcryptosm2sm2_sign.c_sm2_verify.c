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
typedef  int /*<<< orphan*/  EC_KEY ;
typedef  int /*<<< orphan*/  ECDSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/ * BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ECDSA_SIG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ECDSA_SIG_new () ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  SM2_F_SM2_VERIFY ; 
 int /*<<< orphan*/  SM2_R_INVALID_ENCODING ; 
 int /*<<< orphan*/  SM2err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * d2i_ECDSA_SIG (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int i2d_ECDSA_SIG (int /*<<< orphan*/ *,unsigned char**) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char*,int) ; 
 int sm2_sig_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int sm2_verify(const unsigned char *dgst, int dgstlen,
               const unsigned char *sig, int sig_len, EC_KEY *eckey)
{
    ECDSA_SIG *s = NULL;
    BIGNUM *e = NULL;
    const unsigned char *p = sig;
    unsigned char *der = NULL;
    int derlen = -1;
    int ret = -1;

    s = ECDSA_SIG_new();
    if (s == NULL) {
        SM2err(SM2_F_SM2_VERIFY, ERR_R_MALLOC_FAILURE);
        goto done;
    }
    if (d2i_ECDSA_SIG(&s, &p, sig_len) == NULL) {
        SM2err(SM2_F_SM2_VERIFY, SM2_R_INVALID_ENCODING);
        goto done;
    }
    /* Ensure signature uses DER and doesn't have trailing garbage */
    derlen = i2d_ECDSA_SIG(s, &der);
    if (derlen != sig_len || memcmp(sig, der, derlen) != 0) {
        SM2err(SM2_F_SM2_VERIFY, SM2_R_INVALID_ENCODING);
        goto done;
    }

    e = BN_bin2bn(dgst, dgstlen, NULL);
    if (e == NULL) {
        SM2err(SM2_F_SM2_VERIFY, ERR_R_BN_LIB);
        goto done;
    }

    ret = sm2_sig_verify(eckey, s, e);

 done:
    OPENSSL_free(der);
    BN_free(e);
    ECDSA_SIG_free(s);
    return ret;
}