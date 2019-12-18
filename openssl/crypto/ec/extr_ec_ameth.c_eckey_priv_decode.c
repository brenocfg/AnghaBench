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
typedef  int /*<<< orphan*/  X509_ALGOR ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECKEY_PRIV_DECODE ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_DECODE_ERROR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS8_pkey_get0 (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,void const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  d2i_ECPrivateKey (int /*<<< orphan*/ **,unsigned char const**,int) ; 
 int /*<<< orphan*/ * eckey_type2param (int,void const*) ; 

__attribute__((used)) static int eckey_priv_decode(EVP_PKEY *pkey, const PKCS8_PRIV_KEY_INFO *p8)
{
    const unsigned char *p = NULL;
    const void *pval;
    int ptype, pklen;
    EC_KEY *eckey = NULL;
    const X509_ALGOR *palg;

    if (!PKCS8_pkey_get0(NULL, &p, &pklen, &palg, p8))
        return 0;
    X509_ALGOR_get0(NULL, &ptype, &pval, palg);

    eckey = eckey_type2param(ptype, pval);

    if (eckey == NULL)
        goto ecliberr;

    /* We have parameters now set private key */
    if (!d2i_ECPrivateKey(&eckey, &p, pklen)) {
        ECerr(EC_F_ECKEY_PRIV_DECODE, EC_R_DECODE_ERROR);
        goto ecerr;
    }

    EVP_PKEY_assign_EC_KEY(pkey, eckey);
    return 1;

 ecliberr:
    ECerr(EC_F_ECKEY_PRIV_DECODE, ERR_R_EC_LIB);
 ecerr:
    EC_KEY_free(eckey);
    return 0;
}