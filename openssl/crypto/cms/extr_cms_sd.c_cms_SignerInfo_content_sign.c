#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  signature; int /*<<< orphan*/  pkey; int /*<<< orphan*/ * pctx; int /*<<< orphan*/  digestAlgorithm; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_1__ CMS_SignerInfo ;
typedef  int /*<<< orphan*/  CMS_ContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  CMS_F_CMS_SIGNERINFO_CONTENT_SIGN ; 
 int /*<<< orphan*/  CMS_R_NO_PRIVATE_KEY ; 
 int /*<<< orphan*/  CMS_R_SIGNFINAL_ERROR ; 
 int /*<<< orphan*/  CMS_SignerInfo_sign (TYPE_1__*) ; 
 int /*<<< orphan*/  CMS_signed_add1_attr_by_NID (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 scalar_t__ CMS_signed_get_attr_count (TYPE_1__*) ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_sign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,unsigned int) ; 
 size_t EVP_PKEY_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_SignFinal (int /*<<< orphan*/ *,unsigned char*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_pkcs9_messageDigest ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  V_ASN1_OCTET_STRING ; 
 int /*<<< orphan*/  cms_DigestAlgorithm_find_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cms_sd_asn1_ctrl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cms_set_si_contentType_attr (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int cms_SignerInfo_content_sign(CMS_ContentInfo *cms,
                                       CMS_SignerInfo *si, BIO *chain)
{
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    int r = 0;
    EVP_PKEY_CTX *pctx = NULL;

    if (mctx == NULL) {
        CMSerr(CMS_F_CMS_SIGNERINFO_CONTENT_SIGN, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    if (!si->pkey) {
        CMSerr(CMS_F_CMS_SIGNERINFO_CONTENT_SIGN, CMS_R_NO_PRIVATE_KEY);
        goto err;
    }

    if (!cms_DigestAlgorithm_find_ctx(mctx, chain, si->digestAlgorithm))
        goto err;
    /* Set SignerInfo algorithm details if we used custom parameter */
    if (si->pctx && !cms_sd_asn1_ctrl(si, 0))
        goto err;

    /*
     * If any signed attributes calculate and add messageDigest attribute
     */

    if (CMS_signed_get_attr_count(si) >= 0) {
        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int mdlen;
        if (!EVP_DigestFinal_ex(mctx, md, &mdlen))
            goto err;
        if (!CMS_signed_add1_attr_by_NID(si, NID_pkcs9_messageDigest,
                                         V_ASN1_OCTET_STRING, md, mdlen))
            goto err;
        /* Copy content type across */
        if (!cms_set_si_contentType_attr(cms, si))
            goto err;

        if (!CMS_SignerInfo_sign(si))
            goto err;
    } else if (si->pctx) {
        unsigned char *sig;
        size_t siglen;
        unsigned char md[EVP_MAX_MD_SIZE];
        unsigned int mdlen;
        pctx = si->pctx;
        if (!EVP_DigestFinal_ex(mctx, md, &mdlen))
            goto err;
        siglen = EVP_PKEY_size(si->pkey);
        sig = OPENSSL_malloc(siglen);
        if (sig == NULL) {
            CMSerr(CMS_F_CMS_SIGNERINFO_CONTENT_SIGN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (EVP_PKEY_sign(pctx, sig, &siglen, md, mdlen) <= 0) {
            OPENSSL_free(sig);
            goto err;
        }
        ASN1_STRING_set0(si->signature, sig, siglen);
    } else {
        unsigned char *sig;
        unsigned int siglen;
        sig = OPENSSL_malloc(EVP_PKEY_size(si->pkey));
        if (sig == NULL) {
            CMSerr(CMS_F_CMS_SIGNERINFO_CONTENT_SIGN, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (!EVP_SignFinal(mctx, sig, &siglen, si->pkey)) {
            CMSerr(CMS_F_CMS_SIGNERINFO_CONTENT_SIGN, CMS_R_SIGNFINAL_ERROR);
            OPENSSL_free(sig);
            goto err;
        }
        ASN1_STRING_set0(si->signature, sig, siglen);
    }

    r = 1;

 err:
    EVP_MD_CTX_free(mctx);
    EVP_PKEY_CTX_free(pctx);
    return r;

}