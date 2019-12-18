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
typedef  int /*<<< orphan*/ * PCERT_PUBLIC_KEY_INFO ;
typedef  int /*<<< orphan*/  HCRYPTPROV_OR_NCRYPT_KEY_HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ CryptExportPublicKeyInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int X509_ASN_ENCODING ; 

PCERT_PUBLIC_KEY_INFO getPublicKeyInfo(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hProv, DWORD dwKeySpec)
{
	PCERT_PUBLIC_KEY_INFO info = NULL;
	DWORD cbInfo;
	if(CryptExportPublicKeyInfo(hProv, dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, NULL, &cbInfo))
	{
		if(info = (PCERT_PUBLIC_KEY_INFO) LocalAlloc(LPTR, cbInfo))
		{
			if(!CryptExportPublicKeyInfo(hProv, dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, info, &cbInfo))
			{
				PRINT_ERROR_AUTO(L"CryptExportPublicKeyInfo (data)");
				info = (PCERT_PUBLIC_KEY_INFO) LocalFree(info);
			}
		}
	}
	else PRINT_ERROR_AUTO(L"CryptExportPublicKeyInfo (init)");
	return info;
}