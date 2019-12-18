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
 int OCSP_REVOKED_STATUS_AACOMPROMISE ; 
 int OCSP_REVOKED_STATUS_NOSTATUS ; 
 int OSSL_CMP_LOG_DEBUG ; 
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
 int OSSL_CRMF_POPO_KEYAGREE ; 
 int OSSL_CRMF_POPO_NONE ; 

int OSSL_CMP_CTX_set_option(OSSL_CMP_CTX *ctx, int opt, int val) {
    int min_val;

    if (ctx == NULL) {
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        return 0;
    }

    switch (opt) {
    case OSSL_CMP_OPT_REVOCATION_REASON:
        min_val = OCSP_REVOKED_STATUS_NOSTATUS;
        break;
    case OSSL_CMP_OPT_POPOMETHOD:
        min_val = OSSL_CRMF_POPO_NONE;
        break;
    default:
        min_val = 0;
        break;
    }
    if (val < min_val) {
        CMPerr(0, CMP_R_INVALID_ARGS);
        return 0;
    }

    switch (opt) {
    case OSSL_CMP_OPT_LOG_VERBOSITY:
        if (val > OSSL_CMP_LOG_DEBUG) {
            CMPerr(0, CMP_R_INVALID_ARGS);
            return 0;
        }
        ctx->log_verbosity = val;
        break;
    case OSSL_CMP_OPT_IMPLICITCONFIRM:
        ctx->implicitConfirm = val;
        break;
    case OSSL_CMP_OPT_DISABLECONFIRM:
        ctx->disableConfirm = val;
        break;
    case OSSL_CMP_OPT_UNPROTECTED_SEND:
        ctx->unprotectedSend = val;
        break;
    case OSSL_CMP_OPT_UNPROTECTED_ERRORS:
        ctx->unprotectedErrors = val;
        break;
    case OSSL_CMP_OPT_VALIDITYDAYS:
        ctx->days = val;
        break;
    case OSSL_CMP_OPT_SUBJECTALTNAME_NODEFAULT:
        ctx->SubjectAltName_nodefault = val;
        break;
    case OSSL_CMP_OPT_SUBJECTALTNAME_CRITICAL:
        ctx->setSubjectAltNameCritical = val;
        break;
    case OSSL_CMP_OPT_POLICIES_CRITICAL:
        ctx->setPoliciesCritical = val;
        break;
    case OSSL_CMP_OPT_IGNORE_KEYUSAGE:
        ctx->ignore_keyusage = val;
        break;
    case OSSL_CMP_OPT_POPOMETHOD:
        if (val > OSSL_CRMF_POPO_KEYAGREE) {
            CMPerr(0, CMP_R_INVALID_ARGS);
            return 0;
        }
        ctx->popoMethod = val;
        break;
    case OSSL_CMP_OPT_DIGEST_ALGNID:
        ctx->digest = val;
        break;
    case OSSL_CMP_OPT_OWF_ALGNID:
        ctx->pbm_owf = val;
        break;
    case OSSL_CMP_OPT_MAC_ALGNID:
        ctx->pbm_mac = val;
        break;
    case OSSL_CMP_OPT_MSGTIMEOUT:
        ctx->msgtimeout = val;
        break;
    case OSSL_CMP_OPT_TOTALTIMEOUT:
        ctx->totaltimeout = val;
        break;
    case OSSL_CMP_OPT_PERMIT_TA_IN_EXTRACERTS_FOR_IR:
        ctx->permitTAInExtraCertsForIR = val;
        break;
    case OSSL_CMP_OPT_REVOCATION_REASON:
        if (val > OCSP_REVOKED_STATUS_AACOMPROMISE) {
            CMPerr(0, CMP_R_INVALID_ARGS);
            return 0;
        }
        ctx->revocationReason = val;
        break;
    default:
        CMPerr(0, CMP_R_INVALID_ARGS);
        return 0;
    }

    return 1;
}