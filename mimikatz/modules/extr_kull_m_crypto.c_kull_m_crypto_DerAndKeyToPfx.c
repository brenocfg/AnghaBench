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
struct TYPE_3__ {int /*<<< orphan*/  pwszContainerName; int /*<<< orphan*/  dwProvType; int /*<<< orphan*/  pwszProvName; int /*<<< orphan*/  member_6; int /*<<< orphan*/ * member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  LPCBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPT_KEY_PROV_INFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AT_KEYEXCHANGE ; 
 int /*<<< orphan*/  CRYPT_EXPORTABLE ; 
 int /*<<< orphan*/  CRYPT_NEWKEYSET ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 scalar_t__ CryptImportKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_ENHANCED_PROV ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  kull_m_crypto_DerAndKeyInfoToPfx (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_crypto_close_hprov_delete_container (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_getRandomGUID () ; 

BOOL kull_m_crypto_DerAndKeyToPfx(LPCVOID der, DWORD derLen, LPCVOID key, DWORD keyLen, BOOL isPvk, LPCWSTR filename) // no PVK support at this time
{
	BOOL isExported = FALSE;
	CRYPT_KEY_PROV_INFO infos = {NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0, 0, NULL, AT_KEYEXCHANGE};
	HCRYPTPROV hCryptProv;
	HCRYPTKEY hCryptKey;
	if(infos.pwszContainerName = kull_m_string_getRandomGUID())
	{
		if(CryptAcquireContext(&hCryptProv, infos.pwszContainerName, infos.pwszProvName, infos.dwProvType, CRYPT_NEWKEYSET))
		{
			if(CryptImportKey(hCryptProv, (LPCBYTE) key,  keyLen, 0, CRYPT_EXPORTABLE, &hCryptKey))
			{
				isExported = kull_m_crypto_DerAndKeyInfoToPfx(der, derLen, &infos, filename);
				CryptDestroyKey(hCryptKey);
			}
			else PRINT_ERROR_AUTO(L"CryptImportKey");
			kull_m_crypto_close_hprov_delete_container(hCryptProv);
			//CryptReleaseContext(hCryptProv, 0);
			//if(!CryptAcquireContext(&hCryptProv, infos.pwszContainerName, NULL, PROV_RSA_FULL, CRYPT_DELETEKEYSET))
			//	PRINT_ERROR(L"Unable to delete temp keyset %s\n", infos.pwszContainerName);
		}
		else PRINT_ERROR_AUTO(L"CryptAcquireContext");
		LocalFree(infos.pwszContainerName);
	}
	return isExported;
}