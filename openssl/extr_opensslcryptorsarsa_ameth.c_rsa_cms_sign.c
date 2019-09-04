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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  CMS_SignerInfo ;
typedef  int /*<<< orphan*/  ASN1_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_SignerInfo_get0_algs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * CMS_SignerInfo_get0_pkey_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_get_rsa_padding (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/  NID_rsaEncryption ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int RSA_PKCS1_PADDING ; 
 int RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rsa_ctx_to_pss_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_cms_sign(CMS_SignerInfo *si)
{
    int pad_mode = RSA_PKCS1_PADDING;
    X509_ALGOR *alg;
    EVP_PKEY_CTX *pkctx = CMS_SignerInfo_get0_pkey_ctx(si);
    ASN1_STRING *os = NULL;

    CMS_SignerInfo_get0_algs(si, NULL, NULL, NULL, &alg);
    if (pkctx) {
        if (EVP_PKEY_CTX_get_rsa_padding(pkctx, &pad_mode) <= 0)
            return 0;
    }
    if (pad_mode == RSA_PKCS1_PADDING) {
        X509_ALGOR_set0(alg, OBJ_nid2obj(NID_rsaEncryption), V_ASN1_NULL, 0);
        return 1;
    }
    /* We don't support it */
    if (pad_mode != RSA_PKCS1_PSS_PADDING)
        return 0;
    os = rsa_ctx_to_pss_string(pkctx);
    if (!os)
        return 0;
    X509_ALGOR_set0(alg, OBJ_nid2obj(EVP_PKEY_RSA_PSS), V_ASN1_SEQUENCE, os);
    return 1;
}