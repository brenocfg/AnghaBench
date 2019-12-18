#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PCERT_NAME_BLOB ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CERT_X500_NAME_STR ; 
 int CertNameToStr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 

PWSTR getCertificateName(PCERT_NAME_BLOB blob)
{
	PWSTR ret = NULL;
	DWORD dwSizeNeeded = CertNameToStr(X509_ASN_ENCODING, blob, CERT_X500_NAME_STR, NULL, 0);
	if(dwSizeNeeded)
	{
		if(ret = (PWSTR) LocalAlloc(LPTR, dwSizeNeeded * sizeof(wchar_t)))
		{
			if(!CertNameToStr(X509_ASN_ENCODING, blob, CERT_X500_NAME_STR, ret, dwSizeNeeded))
				ret = (PWSTR) LocalFree(ret);
		}
	}
	return ret;
}