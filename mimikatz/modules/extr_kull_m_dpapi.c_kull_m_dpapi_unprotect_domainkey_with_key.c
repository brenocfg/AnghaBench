#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int dwSecretLen; int pbSecret; int dwAccesscheckLen; int pbAccesscheck; } ;
struct TYPE_17__ {int buffer; int cbMasterKey; scalar_t__ dataLen; scalar_t__ data; } ;
typedef  TYPE_1__* PVOID ;
typedef  TYPE_1__* PSID ;
typedef  TYPE_3__* PKULL_M_DPAPI_MASTERKEY_DOMAINKEY ;
typedef  TYPE_1__* PKULL_M_DPAPI_DOMAIN_RSA_MASTER_KEY ;
typedef  TYPE_1__* PKULL_M_DPAPI_DOMAIN_ACCESS_CHECK ;
typedef  int PBYTE ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_3DES ; 
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 int /*<<< orphan*/  CopySid (int,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptImportKey (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptSetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLengthSid (TYPE_1__*) ; 
 int /*<<< orphan*/  KP_IV ; 
 int /*<<< orphan*/  LPTR ; 
 TYPE_1__* LocalAlloc (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* LocalFree (TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,int,int) ; 
 scalar_t__ RtlEqualMemory (int,int /*<<< orphan*/ *,int) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kull_m_crypto_close_hprov_delete_container (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_crypto_hash (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_crypto_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_dpapi_unprotect_domainkey_with_key(PKULL_M_DPAPI_MASTERKEY_DOMAINKEY domainkey, LPCVOID key, DWORD keyLen, PVOID *output, DWORD *outputLen, PSID *sid)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv, hSessionProv;
	HCRYPTKEY hKey, hSessionKey;
	PKULL_M_DPAPI_DOMAIN_RSA_MASTER_KEY rsa_buffer;
	PKULL_M_DPAPI_DOMAIN_ACCESS_CHECK des_buffer;
	BYTE digest[SHA_DIGEST_LENGTH];
	DWORD cbOutput;
	PSID pSid;
	
	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(CryptImportKey(hProv, (PBYTE) key, keyLen, 0, 0, &hKey))
		{
			cbOutput = domainkey->dwSecretLen;
			if(rsa_buffer = (PKULL_M_DPAPI_DOMAIN_RSA_MASTER_KEY) LocalAlloc(LPTR, cbOutput))
			{
				RtlCopyMemory(rsa_buffer, domainkey->pbSecret, cbOutput);
				if(CryptDecrypt(hKey, 0, TRUE, 0, (PBYTE) rsa_buffer, &cbOutput))
				{
					//kprintf(L"\nRSA decrypt is a success\n");
					//kprintf(L" * MasterKey len: %u\n", rsa_buffer->cbMasterKey);
					//kull_m_string_wprintf_hex(rsa_buffer->buffer, rsa_buffer->cbMasterKey, 1 | (16 << 16));
					//kprintf(L" * SuppKey   len: %u\n", rsa_buffer->cbSuppKey);
					//kull_m_string_wprintf_hex(rsa_buffer->buffer + rsa_buffer->cbMasterKey, rsa_buffer->cbSuppKey, 1 | (16 << 16));
					if(kull_m_crypto_hkey(hProv, CALG_3DES, rsa_buffer->buffer + rsa_buffer->cbMasterKey, 192 / 8, 0, &hSessionKey, &hSessionProv))
					{
						if(CryptSetKeyParam(hSessionKey, KP_IV, rsa_buffer->buffer + rsa_buffer->cbMasterKey + 192 / 8, 0))
						{
							cbOutput = domainkey->dwAccesscheckLen;

							if(des_buffer = (PKULL_M_DPAPI_DOMAIN_ACCESS_CHECK) LocalAlloc(LPTR, cbOutput))
							{
								RtlCopyMemory(des_buffer, domainkey->pbAccesscheck, cbOutput);

								if(CryptDecrypt(hSessionKey, 0, FALSE, 0, (PBYTE) des_buffer, &cbOutput))
								{
									pSid = (PSID) (des_buffer->data + des_buffer->dataLen);
									//kprintf(L"\n3DES decrypt is a success too\n");
									////kull_m_string_wprintf_hex(des_buffer, outSize, 1 | (16 << 16)); kprintf(L"\n");
									//kprintf(L" * nonce    : "); kull_m_string_wprintf_hex(des_buffer->data, des_buffer->dataLen, 0); kprintf(L"\n"); // try to leave it as is =)
									//kprintf(L" * SID      : "); kull_m_string_displaySID(pSid); kprintf(L"\n");
									//kprintf(L" * SHA1     : "); kull_m_string_wprintf_hex((PBYTE) des_buffer + cbOutput - SHA_DIGEST_LENGTH, SHA_DIGEST_LENGTH, 0); kprintf(L"\n");
									if(kull_m_crypto_hash(CALG_SHA1, des_buffer, cbOutput - SHA_DIGEST_LENGTH, digest, SHA_DIGEST_LENGTH))
									{
										//kprintf(L" > Calc SHA1: "); kull_m_string_wprintf_hex(digest, SHA_DIGEST_LENGTH, 0); kprintf(L"\n");
										if(RtlEqualMemory((PBYTE) des_buffer + cbOutput - SHA_DIGEST_LENGTH, digest, SHA_DIGEST_LENGTH))
										{
											*outputLen = rsa_buffer->cbMasterKey;
											if(*output = LocalAlloc(LPTR, *outputLen))
											{
												RtlCopyMemory(*output, rsa_buffer->buffer, *outputLen);
												status = TRUE;
												*sid = NULL;
												if(sid)
												{
													status = FALSE;
													cbOutput = GetLengthSid(pSid);
													if(*sid = (PSID) LocalAlloc(LPTR, cbOutput))
														status = CopySid(cbOutput, *sid, pSid);
												}
												if(!status)
												{
													if(*output)
														*output = LocalFree(*output);
													if(*sid)
														*sid = LocalFree(*sid);
													*outputLen = 0;
												}
											}
										}
									}
								}
								else PRINT_ERROR_AUTO(L"CryptDecrypt");
								LocalFree(des_buffer);
							}
						}
						else PRINT_ERROR_AUTO(L"CryptSetKeyParam");
						CryptDestroyKey(hSessionKey);
						if(!kull_m_crypto_close_hprov_delete_container(hSessionProv))
							PRINT_ERROR_AUTO(L"kull_m_crypto_close_hprov_delete_container");
					}
				}
				else PRINT_ERROR_AUTO(L"CryptDecrypt");
				LocalFree(rsa_buffer);
			}
			CryptDestroyKey(hKey);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}