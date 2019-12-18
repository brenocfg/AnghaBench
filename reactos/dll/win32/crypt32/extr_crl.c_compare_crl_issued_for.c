#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* pIssuerCert; } ;
struct TYPE_10__ {TYPE_3__* pCrlInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/  Issuer; } ;
struct TYPE_8__ {TYPE_1__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_7__ {int /*<<< orphan*/  Issuer; } ;
typedef  TYPE_4__* PCCRL_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_5__ CRL_FIND_ISSUED_FOR_PARA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertCompareCertificateName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL compare_crl_issued_for(PCCRL_CONTEXT pCrlContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    const CRL_FIND_ISSUED_FOR_PARA *para = pvPara;
    BOOL ret;

    ret = CertCompareCertificateName(para->pIssuerCert->dwCertEncodingType,
     &para->pIssuerCert->pCertInfo->Issuer, &pCrlContext->pCrlInfo->Issuer);
    return ret;
}