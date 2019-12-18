#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int log_verbosity; int implicitConfirm; int disableConfirm; int unprotectedSend; int unprotectedErrors; int days; int SubjectAltName_nodefault; int setSubjectAltNameCritical; int setPoliciesCritical; int ignore_keyusage; int popoMethod; int digest; int pbm_owf; int pbm_mac; int msgtimeout; int totaltimeout; int permitTAInExtraCertsForIR; int revocationReason; } ;
typedef  TYPE_1__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_INVALID_ARGS ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  OSSL_CMP_OPT_DIGEST_ALGNID 145 
#define  OSSL_CMP_OPT_DISABLECONFIRM 144 
#define  OSSL_CMP_OPT_IGNORE_KEYUSAGE 143 
#define  OSSL_CMP_OPT_IMPLICITCONFIRM 142 
#define  OSSL_CMP_OPT_LOG_VERBOSITY 141 
#define  OSSL_CMP_OPT_MAC_ALGNID 140 
#define  OSSL_CMP_OPT_MSGTIMEOUT 139 
#define  OSSL_CMP_OPT_OWF_ALGNID 138 
#define  OSSL_CMP_OPT_PERMIT_TA_IN_EXTRACERTS_FOR_IR 137 
#define  OSSL_CMP_OPT_POLICIES_CRITICAL 136 
#define  OSSL_CMP_OPT_POPOMETHOD 135 
#define  OSSL_CMP_OPT_REVOCATION_REASON 134 
#define  OSSL_CMP_OPT_SUBJECTALTNAME_CRITICAL 133 
#define  OSSL_CMP_OPT_SUBJECTALTNAME_NODEFAULT 132 
#define  OSSL_CMP_OPT_TOTALTIMEOUT 131 
#define  OSSL_CMP_OPT_UNPROTECTED_ERRORS 130 
#define  OSSL_CMP_OPT_UNPROTECTED_SEND 129 
#define  OSSL_CMP_OPT_VALIDITYDAYS 128 

int OSSL_CMP_CTX_get_option(const OSSL_CMP_CTX *ctx, int opt) {
    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return -1;
    }

    switch (opt) {
    case OSSL_CMP_OPT_LOG_VERBOSITY:
        return ctx->log_verbosity;
    case OSSL_CMP_OPT_IMPLICITCONFIRM:
        return ctx->implicitConfirm;
    case OSSL_CMP_OPT_DISABLECONFIRM:
        return ctx->disableConfirm;
    case OSSL_CMP_OPT_UNPROTECTED_SEND:
        return ctx->unprotectedSend;
    case OSSL_CMP_OPT_UNPROTECTED_ERRORS:
        return ctx->unprotectedErrors;
    case OSSL_CMP_OPT_VALIDITYDAYS:
        return ctx->days;
    case OSSL_CMP_OPT_SUBJECTALTNAME_NODEFAULT:
        return ctx->SubjectAltName_nodefault;
    case OSSL_CMP_OPT_SUBJECTALTNAME_CRITICAL:
        return ctx->setSubjectAltNameCritical;
    case OSSL_CMP_OPT_POLICIES_CRITICAL:
        return ctx->setPoliciesCritical;
    case OSSL_CMP_OPT_IGNORE_KEYUSAGE:
        return ctx->ignore_keyusage;
    case OSSL_CMP_OPT_POPOMETHOD:
        return ctx->popoMethod;
    case OSSL_CMP_OPT_DIGEST_ALGNID:
        return ctx->digest;
    case OSSL_CMP_OPT_OWF_ALGNID:
        return ctx->pbm_owf;
    case OSSL_CMP_OPT_MAC_ALGNID:
        return ctx->pbm_mac;
    case OSSL_CMP_OPT_MSGTIMEOUT:
        return ctx->msgtimeout;
    case OSSL_CMP_OPT_TOTALTIMEOUT:
        return ctx->totaltimeout;
    case OSSL_CMP_OPT_PERMIT_TA_IN_EXTRACERTS_FOR_IR:
        return ctx->permitTAInExtraCertsForIR;
    case OSSL_CMP_OPT_REVOCATION_REASON:
        return ctx->revocationReason;
    default:
        CMPerr(0, CMP_R_INVALID_ARGS);
        return -1;
    }
}