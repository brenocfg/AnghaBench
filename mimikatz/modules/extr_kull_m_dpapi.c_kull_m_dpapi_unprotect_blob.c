#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int dwAlgHashLen; int dwAlgCryptLen; scalar_t__ algCrypt; int dwDataLen; int /*<<< orphan*/  pbData; scalar_t__ algHash; int /*<<< orphan*/  dwSaltLen; int /*<<< orphan*/  pbSalt; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PKULL_M_DPAPI_BLOB ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  LPCVOID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int BOOL ;
typedef  scalar_t__ ALG_ID ;

/* Variables and functions */
 scalar_t__ CALG_3DES ; 
 scalar_t__ CALG_SHA1 ; 
 scalar_t__ CALG_SHA_512 ; 
 int CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_crypto_DeriveKeyRaw (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_crypto_close_hprov_delete_container (int /*<<< orphan*/ ) ; 
 int kull_m_crypto_hash (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_crypto_hkey_session (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_dpapi_sessionkey (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int wcslen (int /*<<< orphan*/ ) ; 

BOOL kull_m_dpapi_unprotect_blob(PKULL_M_DPAPI_BLOB blob, LPCVOID masterkey, DWORD masterkeyLen, LPCVOID entropy, DWORD entropyLen, LPCWSTR password, LPVOID *dataOut, DWORD *dataOutLen)
{
	BOOL status = FALSE, iStatus = !password;
	PVOID hmac, key, hashPassword = NULL;
	HCRYPTPROV hSessionProv;
	HCRYPTKEY hSessionKey;
	DWORD hashLen =  blob->dwAlgHashLen / 8, cryptLen = blob->dwAlgCryptLen / 8, hashPasswordLen;
	ALG_ID passwordHash;

	if((blob->algCrypt == CALG_3DES) && (cryptLen < (192 / 8)))
		cryptLen = 192 / 8;

	if(!iStatus)
	{
		if(blob->algHash == CALG_SHA_512)
		{
			passwordHash = CALG_SHA_512;
			hashPasswordLen = hashLen;
		}
		else
		{
			passwordHash = CALG_SHA1;
			hashPasswordLen = SHA_DIGEST_LENGTH;
		}
		if(hashPassword = LocalAlloc(LPTR, hashPasswordLen))
			iStatus = kull_m_crypto_hash(passwordHash, password, (DWORD) (wcslen(password) * sizeof(wchar_t)), hashPassword, hashPasswordLen);
	}

	if(iStatus)
	{
		if(hmac = LocalAlloc(LPTR, hashLen))
		{
			if(kull_m_dpapi_sessionkey(masterkey, masterkeyLen, blob->pbSalt, blob->dwSaltLen, entropy, entropyLen, hashPassword, hashPassword ? hashPasswordLen : 0, blob->algHash, hmac, hashLen))
			{
				if(key = LocalAlloc(LPTR, cryptLen))
				{
					if(kull_m_crypto_DeriveKeyRaw(blob->algHash, hmac, hashLen, key, cryptLen))
					{
						if(kull_m_crypto_hkey_session(blob->algCrypt, key, cryptLen, 0, &hSessionKey, &hSessionProv))
						{
							if(*dataOut = LocalAlloc(LPTR, blob->dwDataLen))
							{
								RtlCopyMemory(*dataOut, blob->pbData, blob->dwDataLen);
								*dataOutLen = blob->dwDataLen;
								status = CryptDecrypt(hSessionKey, 0, TRUE, 0, (LPBYTE) *dataOut, dataOutLen);
								if(!status)
								{
									LocalFree(*dataOut);	
									PRINT_ERROR_AUTO(L"CryptDecrypt");
								}
							}
							CryptDestroyKey(hSessionKey);
							if(!kull_m_crypto_close_hprov_delete_container(hSessionProv))
								PRINT_ERROR_AUTO(L"kull_m_crypto_close_hprov_delete_container");
						}
						else PRINT_ERROR_AUTO(L"kull_m_crypto_hkey_session");
					}
					LocalFree(key);
				}
			}
			LocalFree(hmac);
		}
	}
	if(hashPassword)
		LocalFree(hashPassword);
	return status;
}