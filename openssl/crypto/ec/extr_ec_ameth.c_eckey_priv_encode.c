#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ec; } ;
struct TYPE_5__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_F_ECKEY_PRIV_ENCODE ; 
 unsigned int EC_KEY_get_enc_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_set_enc_flags (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int EC_PKEY_NO_PARAMETERS ; 
 int /*<<< orphan*/  EC_R_DECODE_ERROR ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_X9_62_id_ecPublicKey ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  PKCS8_pkey_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,unsigned char*,int) ; 
 int /*<<< orphan*/  eckey_param2type (int*,void**,int /*<<< orphan*/ *) ; 
 int i2d_ECPrivateKey (int /*<<< orphan*/ *,unsigned char**) ; 

__attribute__((used)) static int eckey_priv_encode(PKCS8_PRIV_KEY_INFO *p8, const EVP_PKEY *pkey)
{
    EC_KEY ec_key = *(pkey->pkey.ec);
    unsigned char *ep, *p;
    int eplen, ptype;
    void *pval;
    unsigned int old_flags;

    if (!eckey_param2type(&ptype, &pval, &ec_key)) {
        ECerr(EC_F_ECKEY_PRIV_ENCODE, EC_R_DECODE_ERROR);
        return 0;
    }

    /* set the private key */

    /*
     * do not include the parameters in the SEC1 private key see PKCS#11
     * 12.11
     */
    old_flags = EC_KEY_get_enc_flags(&ec_key);
    EC_KEY_set_enc_flags(&ec_key, old_flags | EC_PKEY_NO_PARAMETERS);

    eplen = i2d_ECPrivateKey(&ec_key, NULL);
    if (!eplen) {
        ECerr(EC_F_ECKEY_PRIV_ENCODE, ERR_R_EC_LIB);
        return 0;
    }
    ep = OPENSSL_malloc(eplen);
    if (ep == NULL) {
        ECerr(EC_F_ECKEY_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    p = ep;
    if (!i2d_ECPrivateKey(&ec_key, &p)) {
        OPENSSL_free(ep);
        ECerr(EC_F_ECKEY_PRIV_ENCODE, ERR_R_EC_LIB);
        return 0;
    }

    if (!PKCS8_pkey_set0(p8, OBJ_nid2obj(NID_X9_62_id_ecPublicKey), 0,
                         ptype, pval, ep, eplen)) {
        OPENSSL_free(ep);
        return 0;
    }

    return 1;
}