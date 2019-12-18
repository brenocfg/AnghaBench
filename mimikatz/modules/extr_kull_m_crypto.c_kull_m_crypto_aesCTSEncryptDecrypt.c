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
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_MODE_CBC ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KP_MODE ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 scalar_t__ kull_m_crypto_aesCTSDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_crypto_aesCTSEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_crypto_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_crypto_aesCTSEncryptDecrypt(DWORD aesCalgId, PVOID data, DWORD szData, PVOID key, DWORD szKey, PVOID pbIV, BOOL encrypt)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	DWORD mode = CRYPT_MODE_CBC;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(kull_m_crypto_hkey(hProv, aesCalgId, key, szKey, 0, &hKey, NULL))
		{
			if(CryptSetKeyParam(hKey, KP_MODE, (LPCBYTE) &mode, 0))
				status = (encrypt ? kull_m_crypto_aesCTSEncrypt(hKey, (PBYTE) data, szData, (PBYTE) pbIV) : kull_m_crypto_aesCTSDecrypt(hKey, (PBYTE) data, szData, (PBYTE) pbIV));
			CryptDestroyKey(hKey);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}