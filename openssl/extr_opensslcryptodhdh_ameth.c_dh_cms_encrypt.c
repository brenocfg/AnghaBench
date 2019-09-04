#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/ * parameter; int /*<<< orphan*/  const* algorithm; } ;
typedef  TYPE_3__ X509_ALGOR ;
struct TYPE_23__ {int flags; } ;
struct TYPE_20__ {TYPE_1__* dh; } ;
struct TYPE_22__ {TYPE_2__ pkey; } ;
struct TYPE_19__ {int /*<<< orphan*/  pub_key; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  TYPE_4__ EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  CMS_RecipientInfo ;
typedef  TYPE_5__ ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_OCTET_STRING ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;
typedef  TYPE_5__ ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 int /*<<< orphan*/  ASN1_STRING_get0_data (int /*<<< orphan*/ *) ; 
 size_t ASN1_STRING_length (int /*<<< orphan*/ *) ; 
 TYPE_5__* ASN1_STRING_new () ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (TYPE_5__*,unsigned char*,int) ; 
 int /*<<< orphan*/  ASN1_TYPE_free (int /*<<< orphan*/ *) ; 
 scalar_t__ ASN1_TYPE_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ASN1_TYPE_new () ; 
 int /*<<< orphan*/ * BN_to_ASN1_INTEGER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CMS_RecipientInfo_get0_pkey_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_RecipientInfo_kari_get0_alg (int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * CMS_RecipientInfo_kari_get0_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMS_RecipientInfo_kari_get0_orig_id (int /*<<< orphan*/ *,TYPE_3__**,TYPE_5__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_type (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_param_to_asn1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_MD_type (int /*<<< orphan*/  const*) ; 
 TYPE_4__* EVP_PKEY_CTX_get0_pkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_get_dh_kdf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int EVP_PKEY_CTX_get_dh_kdf_type (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set0_dh_kdf_oid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set0_dh_kdf_ukm (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ EVP_PKEY_CTX_set_dh_kdf_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ EVP_PKEY_CTX_set_dh_kdf_outlen (int /*<<< orphan*/ *,int) ; 
 scalar_t__ EVP_PKEY_CTX_set_dh_kdf_type (int /*<<< orphan*/ *,int) ; 
 int EVP_PKEY_DH_KDF_NONE ; 
 int EVP_PKEY_DH_KDF_X9_42 ; 
 int /*<<< orphan*/ * EVP_sha1 () ; 
 int NID_dhpublicnumber ; 
 int NID_id_smime_alg_ESDH ; 
 scalar_t__ NID_sha1 ; 
 scalar_t__ NID_undef ; 
 int /*<<< orphan*/  const* OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_memdup (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  V_ASN1_UNDEF ; 
 int /*<<< orphan*/  X509_ALGOR_free (TYPE_3__*) ; 
 int /*<<< orphan*/  X509_ALGOR_get0 (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* X509_ALGOR_new () ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int i2d_ASN1_INTEGER (int /*<<< orphan*/ *,unsigned char**) ; 
 int i2d_X509_ALGOR (TYPE_3__*,unsigned char**) ; 

__attribute__((used)) static int dh_cms_encrypt(CMS_RecipientInfo *ri)
{
    EVP_PKEY_CTX *pctx;
    EVP_PKEY *pkey;
    EVP_CIPHER_CTX *ctx;
    int keylen;
    X509_ALGOR *talg, *wrap_alg = NULL;
    const ASN1_OBJECT *aoid;
    ASN1_BIT_STRING *pubkey;
    ASN1_STRING *wrap_str;
    ASN1_OCTET_STRING *ukm;
    unsigned char *penc = NULL, *dukm = NULL;
    int penclen;
    size_t dukmlen = 0;
    int rv = 0;
    int kdf_type, wrap_nid;
    const EVP_MD *kdf_md;
    pctx = CMS_RecipientInfo_get0_pkey_ctx(ri);
    if (!pctx)
        return 0;
    /* Get ephemeral key */
    pkey = EVP_PKEY_CTX_get0_pkey(pctx);
    if (!CMS_RecipientInfo_kari_get0_orig_id(ri, &talg, &pubkey,
                                             NULL, NULL, NULL))
        goto err;
    X509_ALGOR_get0(&aoid, NULL, NULL, talg);
    /* Is everything uninitialised? */
    if (aoid == OBJ_nid2obj(NID_undef)) {
        ASN1_INTEGER *pubk = BN_to_ASN1_INTEGER(pkey->pkey.dh->pub_key, NULL);
        if (!pubk)
            goto err;
        /* Set the key */

        penclen = i2d_ASN1_INTEGER(pubk, &penc);
        ASN1_INTEGER_free(pubk);
        if (penclen <= 0)
            goto err;
        ASN1_STRING_set0(pubkey, penc, penclen);
        pubkey->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
        pubkey->flags |= ASN1_STRING_FLAG_BITS_LEFT;

        penc = NULL;
        X509_ALGOR_set0(talg, OBJ_nid2obj(NID_dhpublicnumber),
                        V_ASN1_UNDEF, NULL);
    }

    /* See if custom parameters set */
    kdf_type = EVP_PKEY_CTX_get_dh_kdf_type(pctx);
    if (kdf_type <= 0)
        goto err;
    if (!EVP_PKEY_CTX_get_dh_kdf_md(pctx, &kdf_md))
        goto err;

    if (kdf_type == EVP_PKEY_DH_KDF_NONE) {
        kdf_type = EVP_PKEY_DH_KDF_X9_42;
        if (EVP_PKEY_CTX_set_dh_kdf_type(pctx, kdf_type) <= 0)
            goto err;
    } else if (kdf_type != EVP_PKEY_DH_KDF_X9_42)
        /* Unknown KDF */
        goto err;
    if (kdf_md == NULL) {
        /* Only SHA1 supported */
        kdf_md = EVP_sha1();
        if (EVP_PKEY_CTX_set_dh_kdf_md(pctx, kdf_md) <= 0)
            goto err;
    } else if (EVP_MD_type(kdf_md) != NID_sha1)
        /* Unsupported digest */
        goto err;

    if (!CMS_RecipientInfo_kari_get0_alg(ri, &talg, &ukm))
        goto err;

    /* Get wrap NID */
    ctx = CMS_RecipientInfo_kari_get0_ctx(ri);
    wrap_nid = EVP_CIPHER_CTX_type(ctx);
    if (EVP_PKEY_CTX_set0_dh_kdf_oid(pctx, OBJ_nid2obj(wrap_nid)) <= 0)
        goto err;
    keylen = EVP_CIPHER_CTX_key_length(ctx);

    /* Package wrap algorithm in an AlgorithmIdentifier */

    wrap_alg = X509_ALGOR_new();
    if (wrap_alg == NULL)
        goto err;
    wrap_alg->algorithm = OBJ_nid2obj(wrap_nid);
    wrap_alg->parameter = ASN1_TYPE_new();
    if (wrap_alg->parameter == NULL)
        goto err;
    if (EVP_CIPHER_param_to_asn1(ctx, wrap_alg->parameter) <= 0)
        goto err;
    if (ASN1_TYPE_get(wrap_alg->parameter) == NID_undef) {
        ASN1_TYPE_free(wrap_alg->parameter);
        wrap_alg->parameter = NULL;
    }

    if (EVP_PKEY_CTX_set_dh_kdf_outlen(pctx, keylen) <= 0)
        goto err;

    if (ukm) {
        dukmlen = ASN1_STRING_length(ukm);
        dukm = OPENSSL_memdup(ASN1_STRING_get0_data(ukm), dukmlen);
        if (!dukm)
            goto err;
    }

    if (EVP_PKEY_CTX_set0_dh_kdf_ukm(pctx, dukm, dukmlen) <= 0)
        goto err;
    dukm = NULL;

    /*
     * Now need to wrap encoding of wrap AlgorithmIdentifier into parameter
     * of another AlgorithmIdentifier.
     */
    penc = NULL;
    penclen = i2d_X509_ALGOR(wrap_alg, &penc);
    if (!penc || !penclen)
        goto err;
    wrap_str = ASN1_STRING_new();
    if (wrap_str == NULL)
        goto err;
    ASN1_STRING_set0(wrap_str, penc, penclen);
    penc = NULL;
    X509_ALGOR_set0(talg, OBJ_nid2obj(NID_id_smime_alg_ESDH),
                    V_ASN1_SEQUENCE, wrap_str);

    rv = 1;

 err:
    OPENSSL_free(penc);
    X509_ALGOR_free(wrap_alg);
    return rv;
}