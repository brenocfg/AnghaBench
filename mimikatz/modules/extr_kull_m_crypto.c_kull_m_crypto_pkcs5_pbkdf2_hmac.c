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
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptCreateHash (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _byteswap_ulong (scalar_t__) ; 
 int /*<<< orphan*/  kull_m_crypto_hmac (scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

BOOL kull_m_crypto_pkcs5_pbkdf2_hmac(DWORD calgid, LPCVOID password, DWORD passwordLen, LPCVOID salt, DWORD saltLen, DWORD iterations, BYTE *key, DWORD keyLen, BOOL isDpapiInternal)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	DWORD sizeHmac, count, i, j, r;
	PBYTE asalt, obuf, d1;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(CryptCreateHash(hProv, calgid, 0, 0, &hHash))
		{
			if(CryptGetHashParam(hHash, HP_HASHVAL, NULL, &sizeHmac, 0))
			{
				if(asalt = (PBYTE) LocalAlloc(LPTR, saltLen + sizeof(DWORD)))
				{
					if(obuf = (PBYTE) LocalAlloc(LPTR, sizeHmac))
					{
						if(d1 = (PBYTE) LocalAlloc(LPTR, sizeHmac))
						{
							status = TRUE;
							RtlCopyMemory(asalt, salt, saltLen);
							for (count = 1; keyLen > 0; count++)
							{
								*(PDWORD) (asalt + saltLen) = _byteswap_ulong(count);
								kull_m_crypto_hmac(calgid, password, passwordLen, asalt, saltLen + 4, d1, sizeHmac);
								RtlCopyMemory(obuf, d1, sizeHmac);
								for (i = 1; i < iterations; i++)
								{
									kull_m_crypto_hmac(calgid, password, passwordLen, d1, sizeHmac, d1, sizeHmac);
									for (j = 0; j < sizeHmac; j++)
										obuf[j] ^= d1[j];
									if(isDpapiInternal) // thank you MS!
										RtlCopyMemory(d1, obuf, sizeHmac);
								}
								r = min(keyLen, sizeHmac);
								RtlCopyMemory(key, obuf, r);
								key += r;
								keyLen -= r;
							}
							LocalFree(d1);
						}
						LocalFree(obuf);
					}
					LocalFree(asalt);
				}
			}
			CryptDestroyHash(hHash);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}