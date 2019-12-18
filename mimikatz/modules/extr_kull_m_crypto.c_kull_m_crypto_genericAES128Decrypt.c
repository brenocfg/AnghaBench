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
typedef  int /*<<< orphan*/  PBYTE ;
typedef  scalar_t__ LPVOID ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_AES_128 ; 
 scalar_t__ CRYPT_MODE_CBC ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  KP_MODE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_crypto_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_crypto_genericAES128Decrypt(LPCVOID pKey, LPCVOID pIV, LPCVOID pData, DWORD dwDataLen, LPVOID *pOut, DWORD *dwOutLen)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD mode = CRYPT_MODE_CBC;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(kull_m_crypto_hkey(hProv, CALG_AES_128, pKey, 16, 0, &hKey, NULL))
		{
			if(CryptSetKeyParam(hKey, KP_MODE, (LPCBYTE) &mode, 0))
			{
				if(CryptSetKeyParam(hKey, KP_IV, (LPCBYTE) pIV, 0))
				{
					if(*pOut = LocalAlloc(LPTR, dwDataLen))
					{
						*dwOutLen = dwDataLen;
						RtlCopyMemory(*pOut, pData, dwDataLen);
						if(!(status = CryptDecrypt(hKey, 0, TRUE, 0, (PBYTE) *pOut, dwOutLen)))
						{
							PRINT_ERROR_AUTO(L"CryptDecrypt");
							*pOut = LocalFree(*pOut);
							*dwOutLen = 0;
						}
					}
				}
				else PRINT_ERROR_AUTO(L"CryptSetKeyParam (IV)");
			}
			else PRINT_ERROR_AUTO(L"CryptSetKeyParam (MODE)");
			CryptDestroyKey(hKey);
		}
		else PRINT_ERROR_AUTO(L"kull_m_crypto_hkey");
		CryptReleaseContext(hProv, 0);
	}
	else PRINT_ERROR_AUTO(L"CryptAcquireContext");
	return status;
}