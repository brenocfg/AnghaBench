#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_12__ {scalar_t__ type; } ;
struct TYPE_11__ {unsigned char* data; int length; } ;
struct TYPE_10__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/  p; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/  g; int /*<<< orphan*/ * pub_key; } ;
typedef  int /*<<< orphan*/  PKCS8_PRIV_KEY_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  TYPE_2__ ASN1_STRING ;
typedef  TYPE_3__ ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_to_BN (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_clear_free (TYPE_3__*) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSA_F_DSA_PRIV_DECODE ; 
 int /*<<< orphan*/  DSA_R_BN_ERROR ; 
 int /*<<< orphan*/  DSA_R_DECODE_ERROR ; 
 int /*<<< orphan*/  DSA_free (TYPE_1__*) ; 
 int /*<<< orphan*/  DSAerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_assign_DSA (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PKCS8_pkey_get0 (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ V_ASN1_NEG_INTEGER ; 
 int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,void const**,int /*<<< orphan*/  const*) ; 
 TYPE_3__* d2i_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 TYPE_1__* d2i_DSAparams (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int dsa_priv_decode(EVP_PKEY *pkey, const PKCS8_PRIV_KEY_INFO *p8)
{
    const unsigned char *p, *pm;
    int pklen, pmlen;
    int ptype;
    const void *pval;
    const ASN1_STRING *pstr;
    const X509_ALGOR *palg;
    ASN1_INTEGER *privkey = NULL;
    BN_CTX *ctx = NULL;

    DSA *dsa = NULL;

    int ret = 0;

    if (!PKCS8_pkey_get0(NULL, &p, &pklen, &palg, p8))
        return 0;
    X509_ALGOR_get0(NULL, &ptype, &pval, palg);

    if ((privkey = d2i_ASN1_INTEGER(NULL, &p, pklen)) == NULL)
        goto decerr;
    if (privkey->type == V_ASN1_NEG_INTEGER || ptype != V_ASN1_SEQUENCE)
        goto decerr;

    pstr = pval;
    pm = pstr->data;
    pmlen = pstr->length;
    if ((dsa = d2i_DSAparams(NULL, &pm, pmlen)) == NULL)
        goto decerr;
    /* We have parameters now set private key */
    if ((dsa->priv_key = BN_secure_new()) == NULL
        || !ASN1_INTEGER_to_BN(privkey, dsa->priv_key)) {
        DSAerr(DSA_F_DSA_PRIV_DECODE, DSA_R_BN_ERROR);
        goto dsaerr;
    }
    /* Calculate public key */
    if ((dsa->pub_key = BN_new()) == NULL) {
        DSAerr(DSA_F_DSA_PRIV_DECODE, ERR_R_MALLOC_FAILURE);
        goto dsaerr;
    }
    if ((ctx = BN_CTX_new()) == NULL) {
        DSAerr(DSA_F_DSA_PRIV_DECODE, ERR_R_MALLOC_FAILURE);
        goto dsaerr;
    }

    BN_set_flags(dsa->priv_key, BN_FLG_CONSTTIME);
    if (!BN_mod_exp(dsa->pub_key, dsa->g, dsa->priv_key, dsa->p, ctx)) {
        DSAerr(DSA_F_DSA_PRIV_DECODE, DSA_R_BN_ERROR);
        goto dsaerr;
    }

    dsa->dirty_cnt++;
    EVP_PKEY_assign_DSA(pkey, dsa);

    ret = 1;
    goto done;

 decerr:
    DSAerr(DSA_F_DSA_PRIV_DECODE, DSA_R_DECODE_ERROR);
 dsaerr:
    DSA_free(dsa);
 done:
    BN_CTX_free(ctx);
    ASN1_STRING_clear_free(privkey);
    return ret;
}