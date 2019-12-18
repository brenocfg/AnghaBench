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
struct TYPE_5__ {int /*<<< orphan*/  dwCertEncodingType; TYPE_1__* pCertInfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  Issuer; int /*<<< orphan*/  Subject; } ;
typedef  TYPE_2__* PCCERT_CONTEXT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CERT_NAME_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CERT_INFO_SUBJECT_FLAG ; 
 int /*<<< orphan*/  CertCompareCertificateName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL compare_cert_by_name(PCCERT_CONTEXT pCertContext, DWORD dwType,
 DWORD dwFlags, const void *pvPara)
{
    CERT_NAME_BLOB *blob = (CERT_NAME_BLOB *)pvPara, *toCompare;
    BOOL ret;

    if (dwType & CERT_INFO_SUBJECT_FLAG)
        toCompare = &pCertContext->pCertInfo->Subject;
    else
        toCompare = &pCertContext->pCertInfo->Issuer;
    ret = CertCompareCertificateName(pCertContext->dwCertEncodingType,
     toCompare, blob);
    return ret;
}