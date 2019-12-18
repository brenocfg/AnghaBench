#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_15__ {size_t __cbElements; TYPE_3__** attributes; } ;
struct TYPE_14__ {int id; size_t szData; scalar_t__ data; } ;
struct TYPE_13__ {TYPE_1__* key; } ;
struct TYPE_12__ {int /*<<< orphan*/  dwKeyBlob; int /*<<< orphan*/  KeyBlob; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_2__* PKULL_M_CRED_VAULT_POLICY ;
typedef  TYPE_3__* PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE ;
typedef  TYPE_4__* PKULL_M_CRED_VAULT_CREDENTIAL ;
typedef  int /*<<< orphan*/  PKULL_M_CRED_VAULT_CLEAR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int AES_128_KEY_SIZE ; 
 int AES_256_KEY_SIZE ; 
 size_t CRYPT_MODE_CBC ; 
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptDecrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  PROV_RSA_AES ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kuhl_m_dpapi_unprotect_raw_or_blob (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,char*) ; 
 scalar_t__ kuhl_m_dpapi_vault_key_type (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  kull_m_cred_vault_clear_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_cred_vault_clear_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_vault_clear_descr (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kull_m_cred_vault_credential_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_cred_vault_credential_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  kull_m_cred_vault_credential_descr (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_2__* kull_m_cred_vault_policy_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_cred_vault_policy_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  kull_m_cred_vault_policy_descr (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ kull_m_cred_vault_policy_key (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,size_t,int) ; 

NTSTATUS kuhl_m_dpapi_vault(int argc, wchar_t * argv[])
{
	PCWSTR inFilePolicy, inFileCred;
	PVOID filePolicy, fileCred, out;
	DWORD szFilePolicy, szFileCred, szOut, len, i, mode = CRYPT_MODE_CBC;
	BYTE aes128[AES_128_KEY_SIZE], aes256[AES_256_KEY_SIZE];
	PKULL_M_CRED_VAULT_POLICY vaultPolicy;
	PKULL_M_CRED_VAULT_CREDENTIAL vaultCredential;
	PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE attribute;
	PKULL_M_CRED_VAULT_CLEAR clear;
	PVOID buffer;
	BOOL isAttr;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	
	if(kull_m_string_args_byName(argc, argv, L"cred", &inFileCred, NULL))
	{
		if(kull_m_file_readData(inFileCred, (PBYTE *) &fileCred, &szFileCred))
		{
			if(vaultCredential = kull_m_cred_vault_credential_create(fileCred))
			{
				kull_m_cred_vault_credential_descr(0, vaultCredential);

				if(kull_m_string_args_byName(argc, argv, L"policy", &inFilePolicy, NULL))
				{
					if(kull_m_file_readData(inFilePolicy, (PBYTE *) &filePolicy, &szFilePolicy))
					{
						if(vaultPolicy = kull_m_cred_vault_policy_create(filePolicy))
						{
							kull_m_cred_vault_policy_descr(0, vaultPolicy);
							if(kuhl_m_dpapi_unprotect_raw_or_blob(vaultPolicy->key->KeyBlob, vaultPolicy->key->dwKeyBlob, NULL, argc, argv, NULL, 0, &out, &szOut, L"Decrypting Policy Keys:\n"))
							{
								if(kull_m_cred_vault_policy_key(out, szOut, aes128, aes256))
								{
									kprintf(L"  AES128 key: "); kull_m_string_wprintf_hex(aes128, AES_128_KEY_SIZE, 0); kprintf(L"\n");
									kprintf(L"  AES256 key: "); kull_m_string_wprintf_hex(aes256, AES_256_KEY_SIZE, 0); kprintf(L"\n\n");
									
									if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
									{
										for(i = 0; i < vaultCredential->__cbElements; i++)
										{
											if(attribute = vaultCredential->attributes[i])
											{
												kprintf(L"  > Attribute %u : ", attribute->id);
												if(attribute->data && (len = attribute->szData))
												{
													if(buffer = LocalAlloc(LPTR, len))
													{
														RtlCopyMemory(buffer, attribute->data, len);
														if(kuhl_m_dpapi_vault_key_type(attribute, hProv, aes128, aes256, &hKey, &isAttr))
														{
															if(CryptDecrypt(hKey, 0, TRUE, 0, (PBYTE) buffer, &len))
															{
																if(isAttr)
																{
																	kull_m_string_wprintf_hex(buffer, len, 0);
																}
																else
																{
																	kprintf(L"\n");
																	if(!attribute->id || (attribute->id == 100))
																	{
																		if(clear = kull_m_cred_vault_clear_create(buffer))
																		{
																			kull_m_cred_vault_clear_descr(1, clear);
																			kull_m_cred_vault_clear_delete(clear);
																		}
																	}
																	else kull_m_string_wprintf_hex(buffer, len, 1 | (16 << 16));
																	kprintf(L"\n");
																}
															}
															else PRINT_ERROR_AUTO(L"CryptDecrypt");
														}
														LocalFree(buffer);
													}
												}
												kprintf(L"\n");
											}
										}
										CryptReleaseContext(hProv, 0);
									}
								}
								LocalFree(out);
							}
							kull_m_cred_vault_policy_delete(vaultPolicy);
						}
						LocalFree(filePolicy);
					}
					else PRINT_ERROR_AUTO(L"kull_m_file_readData (policy)");
				}
				kull_m_cred_vault_credential_delete(vaultCredential);
			}
			LocalFree(fileCred);
		}
		else PRINT_ERROR_AUTO(L"kull_m_file_readData (cred)");
	}
	else PRINT_ERROR(L"Input Cred file needed (/cred:file)\n");
				
	return STATUS_SUCCESS;
}