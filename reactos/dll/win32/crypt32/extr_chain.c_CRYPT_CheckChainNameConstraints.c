#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int dwErrorStatus; int /*<<< orphan*/  dwInfoStatus; } ;
struct TYPE_8__ {int /*<<< orphan*/  pCertInfo; } ;
struct TYPE_7__ {int cElement; TYPE_1__** rgpElement; int /*<<< orphan*/  TrustStatus; } ;
struct TYPE_6__ {TYPE_4__ TrustStatus; TYPE_3__* pCertContext; } ;
typedef  TYPE_2__* PCERT_SIMPLE_CHAIN ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CERT_NAME_CONSTRAINTS_INFO ;

/* Variables and functions */
 int CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT ; 
 int /*<<< orphan*/  CERT_TRUST_HAS_VALID_NAME_CONSTRAINTS ; 
 int /*<<< orphan*/  CRYPT_CheckNameConstraints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CRYPT_CombineTrustStatus (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/ * CRYPT_GetNameConstraints (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPT_IsCertificateSelfSigned (TYPE_3__*) ; 
 int /*<<< orphan*/  CRYPT_IsValidNameConstraint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CRYPT_CheckChainNameConstraints(PCERT_SIMPLE_CHAIN chain)
{
    int i, j;

    /* Microsoft's implementation appears to violate RFC 3280:  according to
     * MSDN, the various CERT_TRUST_*_NAME_CONSTRAINT errors are set if a CA's
     * name constraint is violated in the end cert.  According to RFC 3280,
     * the constraints should be checked against every subsequent certificate
     * in the chain, not just the end cert.
     * Microsoft's implementation also sets the name constraint errors on the
     * certs whose constraints were violated, not on the certs that violated
     * them.
     * In order to be error-compatible with Microsoft's implementation, while
     * still adhering to RFC 3280, I use a O(n ^ 2) algorithm to check name
     * constraints.
     */
    for (i = chain->cElement - 1; i > 0; i--)
    {
        CERT_NAME_CONSTRAINTS_INFO *nameConstraints;

        if ((nameConstraints = CRYPT_GetNameConstraints(
         chain->rgpElement[i]->pCertContext->pCertInfo)))
        {
            if (!CRYPT_IsValidNameConstraint(nameConstraints))
                chain->rgpElement[i]->TrustStatus.dwErrorStatus |=
                 CERT_TRUST_HAS_NOT_SUPPORTED_NAME_CONSTRAINT;
            else
            {
                for (j = i - 1; j >= 0; j--)
                {
                    DWORD errorStatus = 0;

                    /* According to RFC 3280, self-signed certs don't have name
                     * constraints checked unless they're the end cert.
                     */
                    if (j == 0 || !CRYPT_IsCertificateSelfSigned(
                     chain->rgpElement[j]->pCertContext))
                    {
                        CRYPT_CheckNameConstraints(nameConstraints,
                         chain->rgpElement[j]->pCertContext->pCertInfo,
                         &errorStatus);
                        if (errorStatus)
                        {
                            chain->rgpElement[i]->TrustStatus.dwErrorStatus |=
                             errorStatus;
                            CRYPT_CombineTrustStatus(&chain->TrustStatus,
                             &chain->rgpElement[i]->TrustStatus);
                        }
                        else
                            chain->rgpElement[i]->TrustStatus.dwInfoStatus |=
                             CERT_TRUST_HAS_VALID_NAME_CONSTRAINTS;
                    }
                }
            }
            LocalFree(nameConstraints);
        }
    }
}