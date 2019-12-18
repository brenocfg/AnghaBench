#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_9__ {int /*<<< orphan*/ * serialNumber; TYPE_2__* issuer; } ;
struct TYPE_7__ {int /*<<< orphan*/  directoryName; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_1__ d; } ;
typedef  TYPE_3__ OSSL_CRMF_CERTID ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_CERTID_GEN ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN_DIRNAME ; 
 int /*<<< orphan*/  OSSL_CRMF_CERTID_free (TYPE_3__*) ; 
 TYPE_3__* OSSL_CRMF_CERTID_new () ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

OSSL_CRMF_CERTID *OSSL_CRMF_CERTID_gen(const X509_NAME *issuer,
                                       const ASN1_INTEGER *serial)
{
    OSSL_CRMF_CERTID *cid = NULL;

    if (issuer == NULL || serial == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_CERTID_GEN, CRMF_R_NULL_ARGUMENT);
        return NULL;
    }

    if ((cid = OSSL_CRMF_CERTID_new()) == NULL)
        goto err;

    if (!X509_NAME_set(&cid->issuer->d.directoryName, issuer))
        goto err;
    cid->issuer->type = GEN_DIRNAME;

    ASN1_INTEGER_free(cid->serialNumber);
    if ((cid->serialNumber = ASN1_INTEGER_dup(serial)) == NULL)
        goto err;

    return cid;

 err:
    OSSL_CRMF_CERTID_free(cid);
    return NULL;
}