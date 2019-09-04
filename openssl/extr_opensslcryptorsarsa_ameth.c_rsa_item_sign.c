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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  ASN1_STRING ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_STRING_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_pkey_ctx (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_CTX_get_rsa_padding (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  EVP_PKEY_RSA_PSS ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int RSA_PKCS1_PADDING ; 
 int RSA_PKCS1_PSS_PADDING ; 
 int /*<<< orphan*/  V_ASN1_SEQUENCE ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rsa_ctx_to_pss_string (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rsa_item_sign(EVP_MD_CTX *ctx, const ASN1_ITEM *it, void *asn,
                         X509_ALGOR *alg1, X509_ALGOR *alg2,
                         ASN1_BIT_STRING *sig)
{
    int pad_mode;
    EVP_PKEY_CTX *pkctx = EVP_MD_CTX_pkey_ctx(ctx);

    if (EVP_PKEY_CTX_get_rsa_padding(pkctx, &pad_mode) <= 0)
        return 0;
    if (pad_mode == RSA_PKCS1_PADDING)
        return 2;
    if (pad_mode == RSA_PKCS1_PSS_PADDING) {
        ASN1_STRING *os1 = NULL;
        os1 = rsa_ctx_to_pss_string(pkctx);
        if (!os1)
            return 0;
        /* Duplicate parameters if we have to */
        if (alg2) {
            ASN1_STRING *os2 = ASN1_STRING_dup(os1);
            if (!os2) {
                ASN1_STRING_free(os1);
                return 0;
            }
            X509_ALGOR_set0(alg2, OBJ_nid2obj(EVP_PKEY_RSA_PSS),
                            V_ASN1_SEQUENCE, os2);
        }
        X509_ALGOR_set0(alg1, OBJ_nid2obj(EVP_PKEY_RSA_PSS),
                        V_ASN1_SEQUENCE, os1);
        return 3;
    }
    return 2;
}