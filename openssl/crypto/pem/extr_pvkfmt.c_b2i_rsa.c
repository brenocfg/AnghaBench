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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_set1_RSA (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEM_F_B2I_RSA ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RSA_new () ; 
 int /*<<< orphan*/  RSA_set0_crt_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_set0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lebn (unsigned char const**,unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  read_ledword (unsigned char const**) ; 

__attribute__((used)) static EVP_PKEY *b2i_rsa(const unsigned char **in,
                         unsigned int bitlen, int ispub)
{
    const unsigned char *pin = *in;
    EVP_PKEY *ret = NULL;
    BIGNUM *e = NULL, *n = NULL, *d = NULL;
    BIGNUM *p = NULL, *q = NULL, *dmp1 = NULL, *dmq1 = NULL, *iqmp = NULL;
    RSA *rsa = NULL;
    unsigned int nbyte, hnbyte;
    nbyte = (bitlen + 7) >> 3;
    hnbyte = (bitlen + 15) >> 4;
    rsa = RSA_new();
    ret = EVP_PKEY_new();
    if (rsa == NULL || ret == NULL)
        goto memerr;
    e = BN_new();
    if (e == NULL)
        goto memerr;
    if (!BN_set_word(e, read_ledword(&pin)))
        goto memerr;
    if (!read_lebn(&pin, nbyte, &n))
        goto memerr;
    if (!ispub) {
        if (!read_lebn(&pin, hnbyte, &p))
            goto memerr;
        if (!read_lebn(&pin, hnbyte, &q))
            goto memerr;
        if (!read_lebn(&pin, hnbyte, &dmp1))
            goto memerr;
        if (!read_lebn(&pin, hnbyte, &dmq1))
            goto memerr;
        if (!read_lebn(&pin, hnbyte, &iqmp))
            goto memerr;
        if (!read_lebn(&pin, nbyte, &d))
            goto memerr;
        if (!RSA_set0_factors(rsa, p, q))
            goto memerr;
        p = q = NULL;
        if (!RSA_set0_crt_params(rsa, dmp1, dmq1, iqmp))
            goto memerr;
        dmp1 = dmq1 = iqmp = NULL;
    }
    if (!RSA_set0_key(rsa, n, e, d))
        goto memerr;
    n = e = d = NULL;

    if (!EVP_PKEY_set1_RSA(ret, rsa))
        goto memerr;
    RSA_free(rsa);
    *in = pin;
    return ret;
 memerr:
    PEMerr(PEM_F_B2I_RSA, ERR_R_MALLOC_FAILURE);
    BN_free(e);
    BN_free(n);
    BN_free(p);
    BN_free(q);
    BN_free(dmp1);
    BN_free(dmq1);
    BN_free(iqmp);
    BN_free(d);
    RSA_free(rsa);
    EVP_PKEY_free(ret);
    return NULL;
}