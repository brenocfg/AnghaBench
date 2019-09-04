#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ entry_type; scalar_t__ version; scalar_t__ log_id_len; scalar_t__ timestamp; int /*<<< orphan*/  sig_len; int /*<<< orphan*/  sig; int /*<<< orphan*/  log_id; } ;
struct TYPE_8__ {scalar_t__ pkeyhashlen; scalar_t__ epoch_time_in_ms; int /*<<< orphan*/ * pkey; int /*<<< orphan*/  pkeyhash; int /*<<< orphan*/ * ihash; } ;
typedef  TYPE_1__ SCT_CTX ;
typedef  TYPE_2__ SCT ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CT_F_SCT_CTX_VERIFY ; 
 scalar_t__ CT_LOG_ENTRY_TYPE_NOT_SET ; 
 scalar_t__ CT_LOG_ENTRY_TYPE_PRECERT ; 
 int /*<<< orphan*/  CT_R_SCT_FUTURE_TIMESTAMP ; 
 int /*<<< orphan*/  CT_R_SCT_INVALID_SIGNATURE ; 
 int /*<<< orphan*/  CT_R_SCT_LOG_ID_MISMATCH ; 
 int /*<<< orphan*/  CT_R_SCT_NOT_SET ; 
 int /*<<< orphan*/  CT_R_SCT_UNSUPPORTED_VERSION ; 
 int /*<<< orphan*/  CTerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 scalar_t__ SCT_VERSION_V1 ; 
 int /*<<< orphan*/  SCT_is_complete (TYPE_2__ const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sct_ctx_update (int /*<<< orphan*/ *,TYPE_1__ const*,TYPE_2__ const*) ; 

int SCT_CTX_verify(const SCT_CTX *sctx, const SCT *sct)
{
    EVP_MD_CTX *ctx = NULL;
    int ret = 0;

    if (!SCT_is_complete(sct) || sctx->pkey == NULL ||
        sct->entry_type == CT_LOG_ENTRY_TYPE_NOT_SET ||
        (sct->entry_type == CT_LOG_ENTRY_TYPE_PRECERT && sctx->ihash == NULL)) {
        CTerr(CT_F_SCT_CTX_VERIFY, CT_R_SCT_NOT_SET);
        return 0;
    }
    if (sct->version != SCT_VERSION_V1) {
        CTerr(CT_F_SCT_CTX_VERIFY, CT_R_SCT_UNSUPPORTED_VERSION);
        return 0;
    }
    if (sct->log_id_len != sctx->pkeyhashlen ||
        memcmp(sct->log_id, sctx->pkeyhash, sctx->pkeyhashlen) != 0) {
        CTerr(CT_F_SCT_CTX_VERIFY, CT_R_SCT_LOG_ID_MISMATCH);
        return 0;
    }
    if (sct->timestamp > sctx->epoch_time_in_ms) {
        CTerr(CT_F_SCT_CTX_VERIFY, CT_R_SCT_FUTURE_TIMESTAMP);
        return 0;
    }

    ctx = EVP_MD_CTX_new();
    if (ctx == NULL)
        goto end;

    if (!EVP_DigestVerifyInit(ctx, NULL, EVP_sha256(), NULL, sctx->pkey))
        goto end;

    if (!sct_ctx_update(ctx, sctx, sct))
        goto end;

    /* Verify signature */
    ret = EVP_DigestVerifyFinal(ctx, sct->sig, sct->sig_len);
    /* If ret < 0 some other error: fall through without setting error */
    if (ret == 0)
        CTerr(CT_F_SCT_CTX_VERIFY, CT_R_SCT_INVALID_SIGNATURE);

end:
    EVP_MD_CTX_free(ctx);
    return ret;
}