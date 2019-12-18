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
struct TYPE_5__ {TYPE_1__* pCertInfo; int /*<<< orphan*/  dwCertEncodingType; } ;
struct TYPE_4__ {int /*<<< orphan*/  SubjectPublicKeyInfo; } ;
typedef  TYPE_2__* PCCERT_CONTEXT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  CERT_PUBLIC_KEY_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CertComparePublicKeyInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL compare_cert_by_public_key(PCCERT_CONTEXT pCertContext,
 DWORD dwType, DWORD dwFlags, const void *pvPara)
{
    CERT_PUBLIC_KEY_INFO *publicKey = (CERT_PUBLIC_KEY_INFO *)pvPara;
    BOOL ret;

    ret = CertComparePublicKeyInfo(pCertContext->dwCertEncodingType,
     &pCertContext->pCertInfo->SubjectPublicKeyInfo, publicKey);
    return ret;
}