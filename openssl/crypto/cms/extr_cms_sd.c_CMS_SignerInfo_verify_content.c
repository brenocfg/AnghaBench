#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  data; scalar_t__ length; } ;
struct TYPE_10__ {TYPE_1__* signature; int /*<<< orphan*/ * pctx; int /*<<< orphan*/  pkey; int /*<<< orphan*/  digestAlgorithm; } ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_2__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  BIO ;
typedef  TYPE_3__ ASN1_OCTET_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT ; 
 int /*<<< orphan*/  CMS_R_ERROR_READING_MESSAGEDIGEST_ATTRIBUTE ; 
 int /*<<< orphan*/  CMS_R_MESSAGEDIGEST_ATTRIBUTE_WRONG_LENGTH ; 
 int /*<<< orphan*/  CMS_R_UNABLE_TO_FINALIZE_CONTEXT ; 
 int /*<<< orphan*/  CMS_R_VERIFICATION_FAILURE ; 
 TYPE_3__* CMS_signed_get0_data_by_OBJ (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CMS_signed_get_attr_count (TYPE_2__*) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_set_signature_md (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int EVP_PKEY_verify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 scalar_t__ EVP_PKEY_verify_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_pkcs9_messageDigest ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  cms_DigestAlgorithm_find_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cms_sd_asn1_ctrl (TYPE_2__*,int) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

int CMS_SignerInfo_verify_content(CMS_SignerInfo *si, BIO *chain)
{
    ASN1_OCTET_STRING *os = NULL;
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX *pkctx = NULL;
    int r = -1;
    unsigned char mval[EVP_MAX_MD_SIZE];
    unsigned int mlen;

    if (mctx == NULL) {
        CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    /* If we have any signed attributes look for messageDigest value */
    if (CMS_signed_get_attr_count(si) >= 0) {
        os = CMS_signed_get0_data_by_OBJ(si,
                                         OBJ_nid2obj(NID_pkcs9_messageDigest),
                                         -3, V_ASN1_OCTET_STRING);
        if (!os) {
            CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT,
                   CMS_R_ERROR_READING_MESSAGEDIGEST_ATTRIBUTE);
            goto err;
        }
    }

    if (!cms_DigestAlgorithm_find_ctx(mctx, chain, si->digestAlgorithm))
        goto err;

    if (EVP_DigestFinal_ex(mctx, mval, &mlen) <= 0) {
        CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT,
               CMS_R_UNABLE_TO_FINALIZE_CONTEXT);
        goto err;
    }

    /* If messageDigest found compare it */

    if (os) {
        if (mlen != (unsigned int)os->length) {
            CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT,
                   CMS_R_MESSAGEDIGEST_ATTRIBUTE_WRONG_LENGTH);
            goto err;
        }

        if (memcmp(mval, os->data, mlen)) {
            CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT,
                   CMS_R_VERIFICATION_FAILURE);
            r = 0;
        } else
            r = 1;
    } else {
        const EVP_MD *md = EVP_MD_CTX_md(mctx);
        pkctx = EVP_PKEY_CTX_new(si->pkey, NULL);
        if (pkctx == NULL)
            goto err;
        if (EVP_PKEY_verify_init(pkctx) <= 0)
            goto err;
        if (EVP_PKEY_CTX_set_signature_md(pkctx, md) <= 0)
            goto err;
        si->pctx = pkctx;
        if (!cms_sd_asn1_ctrl(si, 1))
            goto err;
        r = EVP_PKEY_verify(pkctx, si->signature->data,
                            si->signature->length, mval, mlen);
        if (r <= 0) {
            CMSerr(CMS_F_CMS_SIGNERINFO_VERIFY_CONTENT,
                   CMS_R_VERIFICATION_FAILURE);
            r = 0;
        }
    }

 err:
    EVP_PKEY_CTX_free(pkctx);
    EVP_MD_CTX_free(mctx);
    return r;

}