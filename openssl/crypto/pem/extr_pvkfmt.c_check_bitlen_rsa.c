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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int BN_num_bytes (int /*<<< orphan*/  const*) ; 
 unsigned int MS_RSA1MAGIC ; 
 unsigned int MS_RSA2MAGIC ; 
 int /*<<< orphan*/  PEM_F_CHECK_BITLEN_RSA ; 
 int /*<<< orphan*/  PEM_R_UNSUPPORTED_KEY_COMPONENTS ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RSA_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_get0_crt_params (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_factors (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int RSA_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_bitlen_rsa(RSA *rsa, int ispub, unsigned int *pmagic)
{
    int nbyte, hnbyte, bitlen;
    const BIGNUM *e;

    RSA_get0_key(rsa, NULL, &e, NULL);
    if (BN_num_bits(e) > 32)
        goto badkey;
    bitlen = RSA_bits(rsa);
    nbyte = RSA_size(rsa);
    hnbyte = (bitlen + 15) >> 4;
    if (ispub) {
        *pmagic = MS_RSA1MAGIC;
        return bitlen;
    } else {
        const BIGNUM *d, *p, *q, *iqmp, *dmp1, *dmq1;

        *pmagic = MS_RSA2MAGIC;

        /*
         * For private key each component must fit within nbyte or hnbyte.
         */
        RSA_get0_key(rsa, NULL, NULL, &d);
        if (BN_num_bytes(d) > nbyte)
            goto badkey;
        RSA_get0_factors(rsa, &p, &q);
        RSA_get0_crt_params(rsa, &dmp1, &dmq1, &iqmp);
        if ((BN_num_bytes(iqmp) > hnbyte)
            || (BN_num_bytes(p) > hnbyte)
            || (BN_num_bytes(q) > hnbyte)
            || (BN_num_bytes(dmp1) > hnbyte)
            || (BN_num_bytes(dmq1) > hnbyte))
            goto badkey;
    }
    return bitlen;
 badkey:
    PEMerr(PEM_F_CHECK_BITLEN_RSA, PEM_R_UNSUPPORTED_KEY_COMPONENTS);
    return 0;
}