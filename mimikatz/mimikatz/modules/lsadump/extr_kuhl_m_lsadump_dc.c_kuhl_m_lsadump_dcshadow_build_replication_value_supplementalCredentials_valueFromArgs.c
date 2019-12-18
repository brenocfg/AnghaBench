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
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int AES_128_KEY_LENGTH ; 
 int AES_256_KEY_LENGTH ; 
 scalar_t__ ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERB_ETYPE_AES128_CTS_HMAC_SHA1_96 ; 
 int /*<<< orphan*/  KERB_ETYPE_AES256_CTS_HMAC_SHA1_96 ; 
 scalar_t__ LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,...) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_hash_data_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_stringToHexBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 
 int swscanf_s (scalar_t__,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_valueFromArgs(LPCWSTR theArg, DWORD count, PWSTR *salt, PBYTE *aes256, PBYTE *aes128)
{
	BOOL status = FALSE;
	int ret;
	wchar_t bSalt[64 + 1] = {0}, bAes256[64 + 1] = {0}, bAes128[64 + 1] = {0};
	UNICODE_STRING uSalt, uAes256, uAes128;
	DWORD size;

	if(theArg)
	{
		*salt = NULL;
		*aes256 = NULL;
		*aes128 = NULL;

		ret = swscanf_s(theArg, L"%[^:]:%[^:]:%s", bSalt, (DWORD) ARRAYSIZE(bSalt), bAes256, (DWORD) ARRAYSIZE(bAes256), bAes128, (DWORD) ARRAYSIZE(bAes128));
		if(ret > 1)
		{
			RtlInitUnicodeString(&uSalt, bSalt);
			kprintf(L"Salt  : %wZ\nAES256: ", &uSalt);
			if(lstrlen(bAes256) != (AES_256_KEY_LENGTH * 2))
			{
				RtlInitUnicodeString(&uAes256, bAes256);
				kprintf(L"(password - %wZ) ", &uAes256);
				kuhl_m_kerberos_hash_data_raw(KERB_ETYPE_AES256_CTS_HMAC_SHA1_96, &uAes256, &uSalt, count, aes256, &size);
			}
			else
			{
				kprintf(L"(hex) ");
				if(!kull_m_string_stringToHexBuffer(bAes256, aes256, &size))
					PRINT_ERROR(L"kull_m_string_stringToHexBuffer(AES256)\n");
			}
			if(*aes256)
			{
				kull_m_string_wprintf_hex(*aes256, size, 0);
				kprintf(L"\n");
				if(status = kull_m_string_copy(salt, bSalt))
				{
					if(ret > 2)
					{
						kprintf(L"AES128: ");
						if(lstrlen(bAes128) != (AES_128_KEY_LENGTH * 2))
						{
							RtlInitUnicodeString(&uAes128, bAes128);
							kprintf(L"(password - %wZ) ", &uAes128);
							kuhl_m_kerberos_hash_data_raw(KERB_ETYPE_AES128_CTS_HMAC_SHA1_96, &uAes128, &uSalt, count, aes128, &size);
						}
						else
						{
							kprintf(L"(hex) ");
							if(!kull_m_string_stringToHexBuffer(bAes128, aes128, &size))
								PRINT_ERROR(L"kull_m_string_stringToHexBuffer(AES128)\n");
						}
						if(*aes128)
						{
							kull_m_string_wprintf_hex(*aes128, size, 0);
							kprintf(L"\n");
						}
					}
				}
				else
				{
					*aes256 = (PBYTE) LocalFree(*aes256);
					PRINT_ERROR_AUTO(L"kull_m_string_copy");
				}
			}
		}
		else PRINT_ERROR(L"Error when parsing argument: %s (ret: %i)\n", theArg, ret);
	}
	else PRINT_ERROR(L"NULL arg\n");
	return status;
}