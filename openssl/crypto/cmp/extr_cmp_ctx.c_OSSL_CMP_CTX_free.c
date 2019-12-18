#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  extraCertsIn; int /*<<< orphan*/  caPubs; int /*<<< orphan*/  newCert; int /*<<< orphan*/  statusString; int /*<<< orphan*/  genm_ITAVs; int /*<<< orphan*/  p10CSR; int /*<<< orphan*/  oldCert; int /*<<< orphan*/  policies; int /*<<< orphan*/  reqExtensions; int /*<<< orphan*/  subjectAltNames; int /*<<< orphan*/  subjectName; int /*<<< orphan*/  issuer; int /*<<< orphan*/  newPkey; int /*<<< orphan*/  extraCertsOut; int /*<<< orphan*/  geninfo_ITAVs; TYPE_4__* recipNonce; TYPE_4__* senderNonce; TYPE_4__* transactionID; int /*<<< orphan*/  recipient; TYPE_4__* secretValue; TYPE_4__* referenceValue; int /*<<< orphan*/  pkey; int /*<<< orphan*/  clCert; int /*<<< orphan*/  untrusted_certs; int /*<<< orphan*/  trusted; int /*<<< orphan*/  expected_sender; int /*<<< orphan*/  validatedSrvCert; int /*<<< orphan*/  srvCert; struct TYPE_5__* proxyName; struct TYPE_5__* serverName; struct TYPE_5__* serverPath; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OCTET_STRING_free (TYPE_4__*) ; 
 int /*<<< orphan*/  ASN1_UTF8STRING_free ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERAL_NAME_free ; 
 int /*<<< orphan*/  OPENSSL_cleanse (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  OSSL_CMP_ITAV_free ; 
 int /*<<< orphan*/  POLICYINFO_free ; 
 int /*<<< orphan*/  X509_EXTENSION_free ; 
 int /*<<< orphan*/  X509_NAME_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_REQ_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_STORE_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ASN1_UTF8STRING_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_GENERAL_NAME_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_OSSL_CMP_ITAV_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_POLICYINFO_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_EXTENSION_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void OSSL_CMP_CTX_free(OSSL_CMP_CTX *ctx)
{
    if (ctx == NULL)
        return;

    OPENSSL_free(ctx->serverPath);
    OPENSSL_free(ctx->serverName);
    OPENSSL_free(ctx->proxyName);

    X509_free(ctx->srvCert);
    X509_free(ctx->validatedSrvCert);
    X509_NAME_free(ctx->expected_sender);
    X509_STORE_free(ctx->trusted);
    sk_X509_pop_free(ctx->untrusted_certs, X509_free);

    X509_free(ctx->clCert);
    EVP_PKEY_free(ctx->pkey);
    ASN1_OCTET_STRING_free(ctx->referenceValue);
    if (ctx->secretValue != NULL)
        OPENSSL_cleanse(ctx->secretValue->data, ctx->secretValue->length);
    ASN1_OCTET_STRING_free(ctx->secretValue);

    X509_NAME_free(ctx->recipient);
    ASN1_OCTET_STRING_free(ctx->transactionID);
    ASN1_OCTET_STRING_free(ctx->senderNonce);
    ASN1_OCTET_STRING_free(ctx->recipNonce);
    sk_OSSL_CMP_ITAV_pop_free(ctx->geninfo_ITAVs, OSSL_CMP_ITAV_free);
    sk_X509_pop_free(ctx->extraCertsOut, X509_free);

    EVP_PKEY_free(ctx->newPkey);
    X509_NAME_free(ctx->issuer);
    X509_NAME_free(ctx->subjectName);
    sk_GENERAL_NAME_pop_free(ctx->subjectAltNames, GENERAL_NAME_free);
    sk_X509_EXTENSION_pop_free(ctx->reqExtensions, X509_EXTENSION_free);
    sk_POLICYINFO_pop_free(ctx->policies, POLICYINFO_free);
    X509_free(ctx->oldCert);
    X509_REQ_free(ctx->p10CSR);

    sk_OSSL_CMP_ITAV_pop_free(ctx->genm_ITAVs, OSSL_CMP_ITAV_free);

    sk_ASN1_UTF8STRING_pop_free(ctx->statusString, ASN1_UTF8STRING_free);
    X509_free(ctx->newCert);
    sk_X509_pop_free(ctx->caPubs, X509_free);
    sk_X509_pop_free(ctx->extraCertsIn, X509_free);

    OPENSSL_free(ctx);
}