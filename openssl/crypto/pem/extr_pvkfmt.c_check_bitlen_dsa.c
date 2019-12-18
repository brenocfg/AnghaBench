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
typedef  int /*<<< orphan*/  DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DSA_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  DSA_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**,int /*<<< orphan*/  const**) ; 
 unsigned int MS_DSS1MAGIC ; 
 unsigned int MS_DSS2MAGIC ; 
 int /*<<< orphan*/  PEM_F_CHECK_BITLEN_DSA ; 
 int /*<<< orphan*/  PEM_R_UNSUPPORTED_KEY_COMPONENTS ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_bitlen_dsa(DSA *dsa, int ispub, unsigned int *pmagic)
{
    int bitlen;
    const BIGNUM *p = NULL, *q = NULL, *g = NULL;
    const BIGNUM *pub_key = NULL, *priv_key = NULL;

    DSA_get0_pqg(dsa, &p, &q, &g);
    DSA_get0_key(dsa, &pub_key, &priv_key);
    bitlen = BN_num_bits(p);
    if ((bitlen & 7) || (BN_num_bits(q) != 160)
        || (BN_num_bits(g) > bitlen))
        goto badkey;
    if (ispub) {
        if (BN_num_bits(pub_key) > bitlen)
            goto badkey;
        *pmagic = MS_DSS1MAGIC;
    } else {
        if (BN_num_bits(priv_key) > 160)
            goto badkey;
        *pmagic = MS_DSS2MAGIC;
    }

    return bitlen;
 badkey:
    PEMerr(PEM_F_CHECK_BITLEN_DSA, PEM_R_UNSUPPORTED_KEY_COMPONENTS);
    return 0;
}