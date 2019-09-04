#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_14__ {unsigned char* data; int length; } ;
struct TYPE_13__ {int /*<<< orphan*/ * pub_key; } ;
struct TYPE_12__ {TYPE_1__* ameth; } ;
struct TYPE_11__ {int /*<<< orphan*/  pkey_id; } ;
typedef  TYPE_2__ EVP_PKEY ;
typedef  TYPE_3__ DH ;
typedef  TYPE_4__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_F_DH_PUB_DECODE ; 
 int /*<<< orphan*/  DH_R_BN_DECODE_ERROR ; 
 int /*<<< orphan*/  DH_R_DECODE_ERROR ; 
 int /*<<< orphan*/  DH_R_PARAMETER_ENCODING_ERROR ; 
 int /*<<< orphan*/  DH_free (TYPE_3__*) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/ *,int*,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0_param (int /*<<< orphan*/ *,unsigned char const**,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char const**,int) ; 
 TYPE_3__* d2i_dhp (TYPE_2__*,unsigned char const**,int) ; 

__attribute__((used)) static int dh_pub_decode(EVP_PKEY *pkey, X509_PUBKEY *pubkey)
{
    const unsigned char *p, *pm;
    int pklen, pmlen;
    int ptype;
    const void *pval;
    const ASN1_STRING *pstr;
    X509_ALGOR *palg;
    ASN1_INTEGER *public_key = NULL;

    DH *dh = NULL;

    if (!X509_PUBKEY_get0_param(NULL, &p, &pklen, &palg, pubkey))
        return 0;
    X509_ALGOR_get0(NULL, &ptype, &pval, palg);

    if (ptype != V_ASN1_SEQUENCE) {
        DHerr(DH_F_DH_PUB_DECODE, DH_R_PARAMETER_ENCODING_ERROR);
        goto err;
    }

    pstr = pval;
    pm = pstr->data;
    pmlen = pstr->length;

    if ((dh = d2i_dhp(pkey, &pm, pmlen)) == NULL) {
        DHerr(DH_F_DH_PUB_DECODE, DH_R_DECODE_ERROR);
        goto err;
    }

    if ((public_key = d2i_ASN1_INTEGER(NULL, &p, pklen)) == NULL) {
        DHerr(DH_F_DH_PUB_DECODE, DH_R_DECODE_ERROR);
        goto err;
    }

    /* We have parameters now set public key */
    if ((dh->pub_key = ASN1_INTEGER_to_BN(public_key, NULL)) == NULL) {
        DHerr(DH_F_DH_PUB_DECODE, DH_R_BN_DECODE_ERROR);
        goto err;
    }

    ASN1_INTEGER_free(public_key);
    EVP_PKEY_assign(pkey, pkey->ameth->pkey_id, dh);
    return 1;

 err:
    ASN1_INTEGER_free(public_key);
    DH_free(dh);
    return 0;

}