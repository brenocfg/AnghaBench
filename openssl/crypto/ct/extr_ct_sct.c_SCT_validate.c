#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_8__ {int /*<<< orphan*/  cert; int /*<<< orphan*/  epoch_time_in_ms; int /*<<< orphan*/ * issuer; int /*<<< orphan*/  log_store; } ;
struct TYPE_7__ {scalar_t__ version; scalar_t__ validation_status; int /*<<< orphan*/  log_id_len; int /*<<< orphan*/  log_id; } ;
typedef  int /*<<< orphan*/  SCT_CTX ;
typedef  TYPE_1__ SCT ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  TYPE_2__ CT_POLICY_EVAL_CTX ;
typedef  int /*<<< orphan*/  CTLOG ;

/* Variables and functions */
 int /*<<< orphan*/ * CTLOG_STORE_get0_log_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CTLOG_get0_public_key (int /*<<< orphan*/  const*) ; 
 scalar_t__ CT_LOG_ENTRY_TYPE_PRECERT ; 
 int /*<<< orphan*/  SCT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SCT_CTX_new () ; 
 int SCT_CTX_set1_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SCT_CTX_set1_issuer_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SCT_CTX_set1_pubkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCT_CTX_set_time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SCT_CTX_verify (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ SCT_VALIDATION_STATUS_INVALID ; 
 scalar_t__ SCT_VALIDATION_STATUS_UNKNOWN_LOG ; 
 scalar_t__ SCT_VALIDATION_STATUS_UNKNOWN_VERSION ; 
 void* SCT_VALIDATION_STATUS_UNVERIFIED ; 
 scalar_t__ SCT_VALIDATION_STATUS_VALID ; 
 scalar_t__ SCT_VERSION_V1 ; 
 scalar_t__ SCT_get_log_entry_type (TYPE_1__*) ; 
 int /*<<< orphan*/  X509_PUBKEY_free (int /*<<< orphan*/ *) ; 
 int X509_PUBKEY_set (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ *) ; 

int SCT_validate(SCT *sct, const CT_POLICY_EVAL_CTX *ctx)
{
    int is_sct_valid = -1;
    SCT_CTX *sctx = NULL;
    X509_PUBKEY *pub = NULL, *log_pkey = NULL;
    const CTLOG *log;

    /*
     * With an unrecognized SCT version we don't know what such an SCT means,
     * let alone validate one.  So we return validation failure (0).
     */
    if (sct->version != SCT_VERSION_V1) {
        sct->validation_status = SCT_VALIDATION_STATUS_UNKNOWN_VERSION;
        return 0;
    }

    log = CTLOG_STORE_get0_log_by_id(ctx->log_store,
                                     sct->log_id, sct->log_id_len);

    /* Similarly, an SCT from an unknown log also cannot be validated. */
    if (log == NULL) {
        sct->validation_status = SCT_VALIDATION_STATUS_UNKNOWN_LOG;
        return 0;
    }

    sctx = SCT_CTX_new();
    if (sctx == NULL)
        goto err;

    if (X509_PUBKEY_set(&log_pkey, CTLOG_get0_public_key(log)) != 1)
        goto err;
    if (SCT_CTX_set1_pubkey(sctx, log_pkey) != 1)
        goto err;

    if (SCT_get_log_entry_type(sct) == CT_LOG_ENTRY_TYPE_PRECERT) {
        EVP_PKEY *issuer_pkey;

        if (ctx->issuer == NULL) {
            sct->validation_status = SCT_VALIDATION_STATUS_UNVERIFIED;
            goto end;
        }

        issuer_pkey = X509_get0_pubkey(ctx->issuer);

        if (X509_PUBKEY_set(&pub, issuer_pkey) != 1)
            goto err;
        if (SCT_CTX_set1_issuer_pubkey(sctx, pub) != 1)
            goto err;
    }

    SCT_CTX_set_time(sctx, ctx->epoch_time_in_ms);

    /*
     * XXX: Potential for optimization.  This repeats some idempotent heavy
     * lifting on the certificate for each candidate SCT, and appears to not
     * use any information in the SCT itself, only the certificate is
     * processed.  So it may make more sense to to do this just once, perhaps
     * associated with the shared (by all SCTs) policy eval ctx.
     *
     * XXX: Failure here is global (SCT independent) and represents either an
     * issue with the certificate (e.g. duplicate extensions) or an out of
     * memory condition.  When the certificate is incompatible with CT, we just
     * mark the SCTs invalid, rather than report a failure to determine the
     * validation status.  That way, callbacks that want to do "soft" SCT
     * processing will not abort handshakes with false positive internal
     * errors.  Since the function does not distinguish between certificate
     * issues (peer's fault) and internal problems (out fault) the safe thing
     * to do is to report a validation failure and let the callback or
     * application decide what to do.
     */
    if (SCT_CTX_set1_cert(sctx, ctx->cert, NULL) != 1)
        sct->validation_status = SCT_VALIDATION_STATUS_UNVERIFIED;
    else
        sct->validation_status = SCT_CTX_verify(sctx, sct) == 1 ?
            SCT_VALIDATION_STATUS_VALID : SCT_VALIDATION_STATUS_INVALID;

end:
    is_sct_valid = sct->validation_status == SCT_VALIDATION_STATUS_VALID;
err:
    X509_PUBKEY_free(pub);
    X509_PUBKEY_free(log_pkey);
    SCT_CTX_free(sctx);

    return is_sct_valid;
}