#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int status; int failInfoCode; int msgtimeout; int pbm_slen; int pbm_itercnt; int /*<<< orphan*/  revocationReason; int /*<<< orphan*/  popoMethod; void* digest; int /*<<< orphan*/  pbm_mac; void* pbm_owf; int /*<<< orphan*/ * untrusted_certs; void* proxyPort; void* serverPort; int /*<<< orphan*/  log_verbosity; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CRL_REASON_NONE ; 
 int /*<<< orphan*/  NID_hmac_sha1 ; 
 void* NID_sha256 ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_free (TYPE_1__*) ; 
 void* OSSL_CMP_DEFAULT_PORT ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_INFO ; 
 int /*<<< orphan*/  OSSL_CRMF_POPO_SIGNATURE ; 
 int /*<<< orphan*/ * sk_X509_new_null () ; 

OSSL_CMP_CTX *OSSL_CMP_CTX_new(void)
{
    OSSL_CMP_CTX *ctx = OPENSSL_zalloc(sizeof(*ctx));

    if (ctx == NULL)
        return NULL;

    ctx->log_verbosity = OSSL_CMP_LOG_INFO;

    ctx->status = -1;
    ctx->failInfoCode = -1;

    ctx->serverPort = OSSL_CMP_DEFAULT_PORT;
    ctx->proxyPort = OSSL_CMP_DEFAULT_PORT;
    ctx->msgtimeout = 2 * 60;

    if ((ctx->untrusted_certs = sk_X509_new_null()) == NULL)
        goto err;

    ctx->pbm_slen = 16;
    ctx->pbm_owf = NID_sha256;
    ctx->pbm_itercnt = 500;
    ctx->pbm_mac = NID_hmac_sha1;

    ctx->digest = NID_sha256;
    ctx->popoMethod = OSSL_CRMF_POPO_SIGNATURE;
    ctx->revocationReason = CRL_REASON_NONE;

    /* all other elements are initialized to 0 or NULL, respectively */
    return ctx;

 err:
    OSSL_CMP_CTX_free(ctx);
    return NULL;
}