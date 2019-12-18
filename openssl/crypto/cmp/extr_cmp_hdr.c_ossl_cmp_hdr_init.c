#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_13__ {int /*<<< orphan*/ * freeText; int /*<<< orphan*/ * transactionID; int /*<<< orphan*/ * recipNonce; int /*<<< orphan*/ * clCert; int /*<<< orphan*/ * oldCert; int /*<<< orphan*/ * issuer; int /*<<< orphan*/ * recipient; int /*<<< orphan*/ * expected_sender; int /*<<< orphan*/ * srvCert; int /*<<< orphan*/ * referenceValue; int /*<<< orphan*/ * subjectName; } ;
struct TYPE_12__ {int /*<<< orphan*/ * senderNonce; int /*<<< orphan*/  transactionID; int /*<<< orphan*/  recipNonce; } ;
typedef  TYPE_1__ OSSL_CMP_PKIHEADER ;
typedef  TYPE_2__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_MISSING_SENDER_IDENTIFICATION ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set1_expected_sender (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set1_senderNonce (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_PVNO ; 
 int /*<<< orphan*/  OSSL_CMP_SENDERNONCE_LENGTH ; 
 int /*<<< orphan*/  OSSL_CMP_TRANSACTIONID_LENGTH ; 
 int /*<<< orphan*/ * X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * X509_get_subject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_assert (int) ; 
 int /*<<< orphan*/  ossl_cmp_asn1_octet_string_set1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_push1_freeText (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set1_recipient (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set1_sender (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_set_pvno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_cmp_hdr_update_messageTime (TYPE_1__*) ; 
 int /*<<< orphan*/  set1_aostr_else_random (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ossl_cmp_hdr_init(OSSL_CMP_CTX *ctx, OSSL_CMP_PKIHEADER *hdr)
{
    X509_NAME *sender;
    X509_NAME *rcp = NULL;

    if (!ossl_assert(ctx != NULL && hdr != NULL))
        return 0;

    /* set the CMP version */
    if (!ossl_cmp_hdr_set_pvno(hdr, OSSL_CMP_PVNO))
        return 0;

    sender = ctx->clCert != NULL ?
        X509_get_subject_name(ctx->clCert) : ctx->subjectName;
    /*
     * The sender name is copied from the subject of the client cert, if any,
     * or else from the the subject name provided for certification requests.
     * As required by RFC 4210 section 5.1.1., if the sender name is not known
     * to the client it set to NULL-DN. In this case for identification at least
     * the senderKID must be set, which we take from any referenceValue given.
     */
    if (sender == NULL && ctx->referenceValue == NULL) {
        CMPerr(0, CMP_R_MISSING_SENDER_IDENTIFICATION);
        return 0;
    }
    if (!ossl_cmp_hdr_set1_sender(hdr, sender))
        return 0;

    /* determine recipient entry in PKIHeader */
    if (ctx->srvCert != NULL) {
        rcp = X509_get_subject_name(ctx->srvCert);
        /* set also as expected_sender of responses unless set explicitly */
        if (ctx->expected_sender == NULL && rcp != NULL
                && !OSSL_CMP_CTX_set1_expected_sender(ctx, rcp))
            return 0;
    } else if (ctx->recipient != NULL) {
        rcp = ctx->recipient;
    } else if (ctx->issuer != NULL) {
        rcp = ctx->issuer;
    } else if (ctx->oldCert != NULL) {
        rcp = X509_get_issuer_name(ctx->oldCert);
    } else if (ctx->clCert != NULL) {
        rcp = X509_get_issuer_name(ctx->clCert);
    }
    if (!ossl_cmp_hdr_set1_recipient(hdr, rcp))
        return 0;

    /* set current time as message time */
    if (!ossl_cmp_hdr_update_messageTime(hdr))
        return 0;

    if (ctx->recipNonce != NULL
            && !ossl_cmp_asn1_octet_string_set1(&hdr->recipNonce,
                                                ctx->recipNonce))
        return 0;

    /*
     * set ctx->transactionID in CMP header
     * if ctx->transactionID is NULL, a random one is created with 128 bit
     * according to section 5.1.1:
     *
     * It is RECOMMENDED that the clients fill the transactionID field with
     * 128 bits of (pseudo-) random data for the start of a transaction to
     * reduce the probability of having the transactionID in use at the server.
     */
    if (ctx->transactionID == NULL
            && !set1_aostr_else_random(&ctx->transactionID, NULL,
                                       OSSL_CMP_TRANSACTIONID_LENGTH))
        return 0;
    if (!ossl_cmp_asn1_octet_string_set1(&hdr->transactionID,
                                         ctx->transactionID))
        return 0;

    /*-
     * set random senderNonce
     * according to section 5.1.1:
     *
     * senderNonce                  present
     *         -- 128 (pseudo-)random bits
     * The senderNonce and recipNonce fields protect the PKIMessage against
     * replay attacks. The senderNonce will typically be 128 bits of
     * (pseudo-) random data generated by the sender, whereas the recipNonce
     * is copied from the senderNonce of the previous message in the
     * transaction.
     */
    if (!set1_aostr_else_random(&hdr->senderNonce, NULL,
                                OSSL_CMP_SENDERNONCE_LENGTH))
        return 0;

    /* store senderNonce - for cmp with recipNonce in next outgoing msg */
    if (!OSSL_CMP_CTX_set1_senderNonce(ctx, hdr->senderNonce))
        return 0;

    /*-
     * freeText                [7] PKIFreeText OPTIONAL,
     * -- this may be used to indicate context-specific instructions
     * -- (this field is intended for human consumption)
     */
    if (ctx->freeText != NULL
            && !ossl_cmp_hdr_push1_freeText(hdr, ctx->freeText))
        return 0;

    return 1;
}