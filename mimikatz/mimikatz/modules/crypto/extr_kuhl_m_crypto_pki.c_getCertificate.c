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
typedef  int /*<<< orphan*/  PCRYPT_ALGORITHM_IDENTIFIER ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  HCRYPTPROV_OR_NCRYPT_KEY_HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ CryptSignAndEncodeCertificate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int PKCS_7_ASN_ENCODING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int X509_ASN_ENCODING ; 

BOOL getCertificate(HCRYPTPROV_OR_NCRYPT_KEY_HANDLE hProv, DWORD dwKeySpec, LPCSTR type, const void *pvStructInfo, PCRYPT_ALGORITHM_IDENTIFIER pSignatureAlgorithm, PBYTE *Certificate, DWORD *cbCertificate)
{
	BOOL status = FALSE;
	if(CryptSignAndEncodeCertificate(hProv, dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, type, pvStructInfo, pSignatureAlgorithm, NULL, NULL, cbCertificate))
	{
		if(*Certificate = (PBYTE) LocalAlloc(LPTR, *cbCertificate))
		{
			if(!(status = CryptSignAndEncodeCertificate(hProv, dwKeySpec, X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, type, pvStructInfo, pSignatureAlgorithm, NULL, *Certificate, cbCertificate)))
			{
				PRINT_ERROR_AUTO(L"CryptSignAndEncodeCertificate (data)");
				*Certificate = (PBYTE) LocalFree(*Certificate);
			}
		}
	}
	else PRINT_ERROR_AUTO(L"CryptSignAndEncodeCertificate (init)");
	return status;
}