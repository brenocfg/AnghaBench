#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_PUBKEY ;
struct TYPE_13__ {TYPE_3__* certTemplate; int /*<<< orphan*/ * publicKey; } ;
struct TYPE_12__ {TYPE_7__* certReq; TYPE_2__* popo; } ;
struct TYPE_11__ {int /*<<< orphan*/  signature; int /*<<< orphan*/  algorithmIdentifier; TYPE_7__* poposkInput; } ;
struct TYPE_10__ {int /*<<< orphan*/ * subject; int /*<<< orphan*/ * publicKey; } ;
struct TYPE_8__ {TYPE_4__* signature; } ;
struct TYPE_9__ {int type; TYPE_1__ value; } ;
typedef  TYPE_4__ OSSL_CRMF_POPOSIGNINGKEY ;
typedef  int /*<<< orphan*/  OSSL_CRMF_MSGS ;
typedef  TYPE_5__ OSSL_CRMF_MSG ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int ASN1_item_verify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_MSGS_VERIFY_POPO ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_POPO_METHOD ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_POPO_NOT_ACCEPTED ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CRMF_CERTREQUEST ; 
 int /*<<< orphan*/  OSSL_CRMF_POPOSIGNINGKEYINPUT ; 
#define  OSSL_CRMF_POPO_KEYAGREE 131 
#define  OSSL_CRMF_POPO_KEYENC 130 
#define  OSSL_CRMF_POPO_RAVERIFIED 129 
#define  OSSL_CRMF_POPO_SIGNATURE 128 
 int /*<<< orphan*/  X509_PUBKEY_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_PUBKEY_get0 (int /*<<< orphan*/ *) ; 
 TYPE_5__* sk_OSSL_CRMF_MSG_value (int /*<<< orphan*/  const*,int) ; 

int OSSL_CRMF_MSGS_verify_popo(const OSSL_CRMF_MSGS *reqs,
                               int rid, int acceptRAVerified)
{
    OSSL_CRMF_MSG *req = NULL;
    X509_PUBKEY *pubkey = NULL;
    OSSL_CRMF_POPOSIGNINGKEY *sig = NULL;

    if (reqs == NULL
            || (req = sk_OSSL_CRMF_MSG_value(reqs, rid)) == NULL
            || req->popo == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_MSGS_VERIFY_POPO,
                CRMF_R_NULL_ARGUMENT);
        return 0;
    }

    switch (req->popo->type) {
    case OSSL_CRMF_POPO_RAVERIFIED:
        if (acceptRAVerified)
            return 1;
        break;
    case OSSL_CRMF_POPO_SIGNATURE:
        pubkey = req->certReq->certTemplate->publicKey;
        sig = req->popo->value.signature;
        if (sig->poposkInput != NULL) {
            /*
             * According to RFC 4211: publicKey contains a copy of
             * the public key from the certificate template. This MUST be
             * exactly the same value as contained in the certificate template.
             */
            if (pubkey == NULL
                    || sig->poposkInput->publicKey == NULL
                    || X509_PUBKEY_cmp(pubkey, sig->poposkInput->publicKey)
                    || ASN1_item_verify(
                           ASN1_ITEM_rptr(OSSL_CRMF_POPOSIGNINGKEYINPUT),
                           sig->algorithmIdentifier, sig->signature,
                           sig->poposkInput, X509_PUBKEY_get0(pubkey)) < 1)
                break;
        } else {
            if (pubkey == NULL
                    || req->certReq->certTemplate->subject == NULL
                    || ASN1_item_verify(ASN1_ITEM_rptr(OSSL_CRMF_CERTREQUEST),
                                    sig->algorithmIdentifier, sig->signature,
                                    req->certReq,
                                    X509_PUBKEY_get0(pubkey)) < 1)
                break;
        }
        return 1;
    case OSSL_CRMF_POPO_KEYENC:
        /*
         * TODO: when OSSL_CMP_certrep_new() supports encrypted certs,
         * return 1 if the type of req->popo->value.keyEncipherment
         * is OSSL_CRMF_POPOPRIVKEY_SUBSEQUENTMESSAGE and
         * its value.subsequentMessage == OSSL_CRMF_SUBSEQUENTMESSAGE_ENCRCERT
        */
    case OSSL_CRMF_POPO_KEYAGREE:
    default:
        CRMFerr(CRMF_F_OSSL_CRMF_MSGS_VERIFY_POPO,
                CRMF_R_UNSUPPORTED_POPO_METHOD);
        return 0;
    }
    CRMFerr(CRMF_F_OSSL_CRMF_MSGS_VERIFY_POPO,
            CRMF_R_UNSUPPORTED_POPO_NOT_ACCEPTED);
    return 0;
}