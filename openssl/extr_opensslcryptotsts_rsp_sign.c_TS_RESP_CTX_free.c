#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  micros; int /*<<< orphan*/  millis; int /*<<< orphan*/  seconds; int /*<<< orphan*/  mds; int /*<<< orphan*/  default_policy; int /*<<< orphan*/  policies; int /*<<< orphan*/  certs; int /*<<< orphan*/  signer_key; int /*<<< orphan*/  signer_cert; } ;
typedef  TYPE_1__ TS_RESP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sk_EVP_MD_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_X509_pop_free (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 

void TS_RESP_CTX_free(TS_RESP_CTX *ctx)
{
    if (!ctx)
        return;

    X509_free(ctx->signer_cert);
    EVP_PKEY_free(ctx->signer_key);
    sk_X509_pop_free(ctx->certs, X509_free);
    sk_ASN1_OBJECT_pop_free(ctx->policies, ASN1_OBJECT_free);
    ASN1_OBJECT_free(ctx->default_policy);
    sk_EVP_MD_free(ctx->mds);   /* No EVP_MD_free method exists. */
    ASN1_INTEGER_free(ctx->seconds);
    ASN1_INTEGER_free(ctx->millis);
    ASN1_INTEGER_free(ctx->micros);
    OPENSSL_free(ctx);
}