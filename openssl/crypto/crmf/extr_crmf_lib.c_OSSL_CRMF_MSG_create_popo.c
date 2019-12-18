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
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * subsequentMessage; } ;
struct TYPE_13__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_3__* popo; int /*<<< orphan*/  certReq; } ;
struct TYPE_10__ {TYPE_7__* keyEncipherment; int /*<<< orphan*/ * signature; int /*<<< orphan*/ * raVerified; } ;
struct TYPE_11__ {int type; TYPE_2__ value; } ;
typedef  int /*<<< orphan*/  OSSL_CRMF_POPOSIGNINGKEY ;
typedef  TYPE_3__ OSSL_CRMF_POPO ;
typedef  TYPE_4__ OSSL_CRMF_MSG ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_new () ; 
 int /*<<< orphan*/  ASN1_INTEGER_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ASN1_NULL_new () ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_MSG_CREATE_POPO ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_METHOD_FOR_CREATING_POPO ; 
 int /*<<< orphan*/  CRMF_poposigningkey_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CRMF_POPOPRIVKEY_SUBSEQUENTMESSAGE ; 
 TYPE_7__* OSSL_CRMF_POPOPRIVKEY_new () ; 
 int /*<<< orphan*/  OSSL_CRMF_POPOSIGNINGKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * OSSL_CRMF_POPOSIGNINGKEY_new () ; 
#define  OSSL_CRMF_POPO_KEYENC 130 
 int OSSL_CRMF_POPO_NONE ; 
#define  OSSL_CRMF_POPO_RAVERIFIED 129 
#define  OSSL_CRMF_POPO_SIGNATURE 128 
 int /*<<< orphan*/  OSSL_CRMF_POPO_free (TYPE_3__*) ; 
 TYPE_3__* OSSL_CRMF_POPO_new () ; 
 int /*<<< orphan*/  OSSL_CRMF_SUBSEQUENTMESSAGE_ENCRCERT ; 

int OSSL_CRMF_MSG_create_popo(OSSL_CRMF_MSG *crm, EVP_PKEY *pkey,
                              int dgst, int ppmtd)
{
    OSSL_CRMF_POPO *pp = NULL;
    ASN1_INTEGER *tag = NULL;

    if (crm == NULL || (ppmtd == OSSL_CRMF_POPO_SIGNATURE && pkey == NULL)) {
        CRMFerr(CRMF_F_OSSL_CRMF_MSG_CREATE_POPO, CRMF_R_NULL_ARGUMENT);
        return 0;
    }

    if (ppmtd == OSSL_CRMF_POPO_NONE)
        goto end;
    if ((pp = OSSL_CRMF_POPO_new()) == NULL)
        goto err;
    pp->type = ppmtd;

    switch (ppmtd) {
    case OSSL_CRMF_POPO_RAVERIFIED:
        if ((pp->value.raVerified = ASN1_NULL_new()) == NULL)
            goto err;
        break;

    case OSSL_CRMF_POPO_SIGNATURE:
        {
            OSSL_CRMF_POPOSIGNINGKEY *ps = OSSL_CRMF_POPOSIGNINGKEY_new();
            if (ps == NULL
                    || !CRMF_poposigningkey_init(ps, crm->certReq, pkey, dgst)){
                OSSL_CRMF_POPOSIGNINGKEY_free(ps);
                goto err;
            }
            pp->value.signature = ps;
        }
        break;

    case OSSL_CRMF_POPO_KEYENC:
        if ((pp->value.keyEncipherment = OSSL_CRMF_POPOPRIVKEY_new()) == NULL)
            goto err;
        tag = ASN1_INTEGER_new();
        pp->value.keyEncipherment->type =
            OSSL_CRMF_POPOPRIVKEY_SUBSEQUENTMESSAGE;
        pp->value.keyEncipherment->value.subsequentMessage = tag;
        if (tag == NULL
                || !ASN1_INTEGER_set(tag, OSSL_CRMF_SUBSEQUENTMESSAGE_ENCRCERT))
            goto err;
        break;

    default:
        CRMFerr(CRMF_F_OSSL_CRMF_MSG_CREATE_POPO,
                CRMF_R_UNSUPPORTED_METHOD_FOR_CREATING_POPO);
        goto err;
    }

 end:
    OSSL_CRMF_POPO_free(crm->popo);
    crm->popo = pp;

    return 1;
 err:
    OSSL_CRMF_POPO_free(pp);
    return 0;
}