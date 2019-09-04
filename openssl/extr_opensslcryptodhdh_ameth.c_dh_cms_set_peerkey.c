#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_ALGOR ;
struct TYPE_16__ {int /*<<< orphan*/ * pub_key; } ;
struct TYPE_13__ {int /*<<< orphan*/  dh; } ;
struct TYPE_15__ {scalar_t__ type; TYPE_2__* ameth; TYPE_1__ pkey; } ;
struct TYPE_14__ {int /*<<< orphan*/  pkey_id; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_3__ EVP_PKEY ;
typedef  TYPE_4__ DH ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_INTEGER_to_BN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_F_DH_CMS_SET_PEERKEY ; 
 int /*<<< orphan*/  DH_R_BN_DECODE_ERROR ; 
 int /*<<< orphan*/  DH_R_DECODE_ERROR ; 
 int /*<<< orphan*/  DH_free (TYPE_4__*) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* DHparams_dup (int /*<<< orphan*/ ) ; 
 TYPE_3__* EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_DHX ; 
 int /*<<< orphan*/  EVP_PKEY_assign (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ EVP_PKEY_derive_set_peer (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_3__*) ; 
 TYPE_3__* EVP_PKEY_new () ; 
 scalar_t__ NID_dhpublicnumber ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/  const*) ; 
 int V_ASN1_NULL ; 
 int V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int*,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int dh_cms_set_peerkey(EVP_PKEY_CTX *pctx,
                              X509_ALGOR *alg, ASN1_BIT_STRING *pubkey)
{
    const ASN1_OBJECT *aoid;
    int atype;
    const void *aval;
    ASN1_INTEGER *public_key = NULL;
    int rv = 0;
    EVP_PKEY *pkpeer = NULL, *pk = NULL;
    DH *dhpeer = NULL;
    const unsigned char *p;
    int plen;

    X509_ALGOR_get0(&aoid, &atype, &aval, alg);
    if (OBJ_obj2nid(aoid) != NID_dhpublicnumber)
        goto err;
    /* Only absent parameters allowed in RFC XXXX */
    if (atype != V_ASN1_UNDEF && atype == V_ASN1_NULL)
        goto err;

    pk = EVP_PKEY_CTX_get0_pkey(pctx);
    if (!pk)
        goto err;
    if (pk->type != EVP_PKEY_DHX)
        goto err;
    /* Get parameters from parent key */
    dhpeer = DHparams_dup(pk->pkey.dh);
    /* We have parameters now set public key */
    plen = ASN1_STRING_length(pubkey);
    p = ASN1_STRING_get0_data(pubkey);
    if (!p || !plen)
        goto err;

    if ((public_key = d2i_ASN1_INTEGER(NULL, &p, plen)) == NULL) {
        DHerr(DH_F_DH_CMS_SET_PEERKEY, DH_R_DECODE_ERROR);
        goto err;
    }

    /* We have parameters now set public key */
    if ((dhpeer->pub_key = ASN1_INTEGER_to_BN(public_key, NULL)) == NULL) {
        DHerr(DH_F_DH_CMS_SET_PEERKEY, DH_R_BN_DECODE_ERROR);
        goto err;
    }

    pkpeer = EVP_PKEY_new();
    if (pkpeer == NULL)
        goto err;
    EVP_PKEY_assign(pkpeer, pk->ameth->pkey_id, dhpeer);
    dhpeer = NULL;
    if (EVP_PKEY_derive_set_peer(pctx, pkpeer) > 0)
        rv = 1;
 err:
    ASN1_INTEGER_free(public_key);
    EVP_PKEY_free(pkpeer);
    DH_free(dhpeer);
    return rv;
}