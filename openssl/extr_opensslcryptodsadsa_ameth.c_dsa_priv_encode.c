#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  priv_key; } ;
struct TYPE_11__ {scalar_t__ length; int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_4__* dsa; } ;
struct TYPE_10__ {TYPE_1__ pkey; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_3__*) ; 
 TYPE_3__* ASN1_STRING_new () ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_F_DSA_PRIV_ENCODE ; 
 int /*<<< orphan*/  DSA_R_BN_ERROR ; 
 int /*<<< orphan*/  DSA_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  NID_dsa ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PKCS8_pkey_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,unsigned char*,int) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char**) ; 
 scalar_t__ i2d_DSAparams (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dsa_priv_encode(PKCS8_PRIV_KEY_INFO *p8, const EVP_PKEY *pkey)
{
    ASN1_STRING *params = NULL;
    ASN1_INTEGER *prkey = NULL;
    unsigned char *dp = NULL;
    int dplen;

    if (!pkey->pkey.dsa || !pkey->pkey.dsa->priv_key) {
        DSAerr(DSA_F_DSA_PRIV_ENCODE, DSA_R_MISSING_PARAMETERS);
        goto err;
    }

    params = ASN1_STRING_new();

    if (params == NULL) {
        DSAerr(DSA_F_DSA_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    params->length = i2d_DSAparams(pkey->pkey.dsa, &params->data);
    if (params->length <= 0) {
        DSAerr(DSA_F_DSA_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    params->type = V_ASN1_SEQUENCE;

    /* Get private key into integer */
    prkey = BN_to_ASN1_INTEGER(pkey->pkey.dsa->priv_key, NULL);

    if (!prkey) {
        DSAerr(DSA_F_DSA_PRIV_ENCODE, DSA_R_BN_ERROR);
        goto err;
    }

    dplen = i2d_ASN1_INTEGER(prkey, &dp);

    ASN1_STRING_clear_free(prkey);
    prkey = NULL;

    if (!PKCS8_pkey_set0(p8, OBJ_nid2obj(NID_dsa), 0,
                         V_ASN1_SEQUENCE, params, dp, dplen))
        goto err;

    return 1;

 err:
    OPENSSL_free(dp);
    ASN1_STRING_free(params);
    ASN1_STRING_clear_free(prkey);
    return 0;
}