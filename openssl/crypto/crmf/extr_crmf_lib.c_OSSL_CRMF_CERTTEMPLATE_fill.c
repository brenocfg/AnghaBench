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
typedef  int /*<<< orphan*/  X509_NAME ;
struct TYPE_3__ {int /*<<< orphan*/  publicKey; int /*<<< orphan*/ * serialNumber; int /*<<< orphan*/  issuer; int /*<<< orphan*/  subject; } ;
typedef  TYPE_1__ OSSL_CRMF_CERTTEMPLATE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/ * ASN1_INTEGER_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ASN1_INTEGER_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_CERTTEMPLATE_FILL ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_PUBKEY_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int OSSL_CRMF_CERTTEMPLATE_fill(OSSL_CRMF_CERTTEMPLATE *tmpl,
                                EVP_PKEY *pubkey,
                                const X509_NAME *subject,
                                const X509_NAME *issuer,
                                const ASN1_INTEGER *serial)
{
    if (tmpl == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_CERTTEMPLATE_FILL, CRMF_R_NULL_ARGUMENT);
        return 0;
    }
    if (subject != NULL && !X509_NAME_set(&tmpl->subject, subject))
        return 0;
    if (issuer != NULL && !X509_NAME_set(&tmpl->issuer, issuer))
        return 0;
    if (serial != NULL) {
        ASN1_INTEGER_free(tmpl->serialNumber);
        if ((tmpl->serialNumber = ASN1_INTEGER_dup(serial)) == NULL)
            return 0;
    }
    if (pubkey != NULL && !X509_PUBKEY_set(&tmpl->publicKey, pubkey))
        return 0;
    return 1;
}