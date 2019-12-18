#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dwErrorStatus; } ;
struct TYPE_5__ {TYPE_1__ TrustStatus; int /*<<< orphan*/  pCertContext; } ;
typedef  TYPE_2__* PCERT_CHAIN_ELEMENT ;
typedef  int /*<<< orphan*/  PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  HCERTSTORE ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_TRUST_IS_UNTRUSTED_ROOT ; 
 int /*<<< orphan*/  CRYPT_FindCertInStore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CertFreeCertificateContext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CRYPT_CheckTrustedStatus(HCERTSTORE hRoot,
 PCERT_CHAIN_ELEMENT rootElement)
{
    PCCERT_CONTEXT trustedRoot = CRYPT_FindCertInStore(hRoot,
     rootElement->pCertContext);

    if (!trustedRoot)
        rootElement->TrustStatus.dwErrorStatus |=
         CERT_TRUST_IS_UNTRUSTED_ROOT;
    else
        CertFreeCertificateContext(trustedRoot);
}