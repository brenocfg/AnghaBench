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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;
typedef  int /*<<< orphan*/  ASN1_BIT_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_F_ASN1_ITEM_SIGN ; 
 int ASN1_item_sign_ctx (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ASN1err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 

int ASN1_item_sign(const ASN1_ITEM *it, X509_ALGOR *algor1,
                   X509_ALGOR *algor2, ASN1_BIT_STRING *signature, void *asn,
                   EVP_PKEY *pkey, const EVP_MD *type)
{
    int rv;
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (ctx == NULL) {
        ASN1err(ASN1_F_ASN1_ITEM_SIGN, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    if (!EVP_DigestSignInit(ctx, NULL, type, NULL, pkey)) {
        EVP_MD_CTX_free(ctx);
        return 0;
    }

    rv = ASN1_item_sign_ctx(it, algor1, algor2, signature, asn, ctx);

    EVP_MD_CTX_free(ctx);
    return rv;
}