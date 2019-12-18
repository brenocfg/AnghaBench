#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  priv_key; } ;
struct TYPE_14__ {scalar_t__ length; int /*<<< orphan*/  type; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_6__* dh; } ;
struct TYPE_13__ {TYPE_2__* ameth; TYPE_1__ pkey; } ;
struct TYPE_12__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  TYPE_4__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_free (TYPE_4__*) ; 
 TYPE_4__* ASN1_STRING_new () ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_F_DH_PRIV_ENCODE ; 
 int /*<<< orphan*/  DH_R_BN_ERROR ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PKCS8_pkey_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,unsigned char*,int) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int i2d_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char**) ; 
 scalar_t__ i2d_dhp (TYPE_3__ const*,TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dh_priv_encode(PKCS8_PRIV_KEY_INFO *p8, const EVP_PKEY *pkey)
{
    ASN1_STRING *params = NULL;
    ASN1_INTEGER *prkey = NULL;
    unsigned char *dp = NULL;
    int dplen;

    params = ASN1_STRING_new();

    if (params == NULL) {
        DHerr(DH_F_DH_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    params->length = i2d_dhp(pkey, pkey->pkey.dh, &params->data);
    if (params->length <= 0) {
        DHerr(DH_F_DH_PRIV_ENCODE, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    params->type = V_ASN1_SEQUENCE;

    /* Get private key into integer */
    prkey = BN_to_ASN1_INTEGER(pkey->pkey.dh->priv_key, NULL);

    if (prkey == NULL) {
        DHerr(DH_F_DH_PRIV_ENCODE, DH_R_BN_ERROR);
        goto err;
    }

    dplen = i2d_ASN1_INTEGER(prkey, &dp);

    ASN1_STRING_clear_free(prkey);
    prkey = NULL;

    if (!PKCS8_pkey_set0(p8, OBJ_nid2obj(pkey->ameth->pkey_id), 0,
                         V_ASN1_SEQUENCE, params, dp, dplen))
        goto err;

    return 1;

 err:
    OPENSSL_free(dp);
    ASN1_STRING_free(params);
    ASN1_STRING_clear_free(prkey);
    return 0;
}