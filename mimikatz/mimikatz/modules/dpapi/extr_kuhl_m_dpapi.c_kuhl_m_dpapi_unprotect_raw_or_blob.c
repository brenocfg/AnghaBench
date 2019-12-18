#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_13__ {int member_0; int member_1; int /*<<< orphan*/  dwPromptFlags; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; } ;
struct TYPE_10__ {int /*<<< orphan*/ * keyHash; } ;
struct TYPE_12__ {TYPE_1__ data; } ;
struct TYPE_11__ {int /*<<< orphan*/  guidMasterKey; } ;
typedef  TYPE_2__* PKULL_M_DPAPI_BLOB ;
typedef  TYPE_3__* PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY ;
typedef  int /*<<< orphan*/ * PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LPCWSTR ;
typedef  int /*<<< orphan*/ * LPCVOID ;
typedef  int DWORD ;
typedef  TYPE_4__ CRYPTPROTECT_PROMPTSTRUCT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CRYPTPROTECT_LOCAL_MACHINE ; 
 int CRYPTPROTECT_PROMPT_ON_PROTECT ; 
 int CRYPTPROTECT_PROMPT_ON_UNPROTECT ; 
 int CRYPTPROTECT_PROMPT_STRONG ; 
 int CRYPTPROTECT_UI_FORBIDDEN ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIMIKATZ ; 
 scalar_t__ NTE_BAD_KEY_STATE ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_masterkey_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_masterkey_descr (TYPE_3__*) ; 
 TYPE_3__* kuhl_m_dpapi_oe_masterkey_get (int /*<<< orphan*/ *) ; 
 TYPE_2__* kull_m_dpapi_blob_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_delete (TYPE_2__*) ; 
 int /*<<< orphan*/  kull_m_dpapi_displayPromptFlags (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_dpapi_unprotect_raw_or_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_4__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_stringToHexBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_dpapi_unprotect_raw_or_blob(LPCVOID pDataIn, DWORD dwDataInLen, LPWSTR *ppszDataDescr, int argc, wchar_t * argv[], LPCVOID pOptionalEntropy, DWORD dwOptionalEntropyLen, LPVOID *pDataOut, DWORD *dwDataOutLen, LPCWSTR pText)
{
	BOOL status = FALSE;
	PCWSTR szEntropy, szMasterkey, szPassword = NULL;
	CRYPTPROTECT_PROMPTSTRUCT promptStructure = {sizeof(CRYPTPROTECT_PROMPTSTRUCT), CRYPTPROTECT_PROMPT_ON_PROTECT | CRYPTPROTECT_PROMPT_ON_UNPROTECT | CRYPTPROTECT_PROMPT_STRONG, NULL, MIMIKATZ}, *pPrompt;

	PBYTE masterkey = NULL, entropy = NULL;
	DWORD masterkeyLen = 0, entropyLen = 0, flags = 0;
	PKULL_M_DPAPI_BLOB blob;
	PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY entry = NULL;
	BOOL isNormalAPI = kull_m_string_args_byName(argc, argv, L"unprotect", NULL, NULL);

	if(kull_m_string_args_byName(argc, argv, L"masterkey", &szMasterkey, NULL))
		kull_m_string_stringToHexBuffer(szMasterkey, &masterkey, &masterkeyLen);
	kull_m_string_args_byName(argc, argv, L"password", &szPassword, NULL);
	if(kull_m_string_args_byName(argc, argv, L"entropy", &szEntropy, NULL))
		kull_m_string_stringToHexBuffer(szEntropy, &entropy, &entropyLen);
	pPrompt = kull_m_string_args_byName(argc, argv, L"prompt", NULL, NULL) ? &promptStructure : NULL;

	if(kull_m_string_args_byName(argc, argv, L"machine", NULL, NULL))
		flags |= CRYPTPROTECT_LOCAL_MACHINE;

	if(blob = kull_m_dpapi_blob_create(pDataIn))
	{
		entry = kuhl_m_dpapi_oe_masterkey_get(&blob->guidMasterKey);
		if(entry || (masterkey && masterkeyLen) || isNormalAPI)
		{
			if(pText)
				kprintf(L"%s", pText);

			if(isNormalAPI)
			{
				kprintf(L" * using CryptUnprotectData API\n");
			}
			
			if(entry)
			{
				kprintf(L" * volatile cache: ");
				kuhl_m_dpapi_oe_masterkey_descr(entry);
			}
			if(masterkey)
			{
				kprintf(L" * masterkey     : ");
				kull_m_string_wprintf_hex(masterkey, masterkeyLen, 0);
				kprintf(L"\n");
			}
			if(pPrompt)
			{
				kprintf(L" > prompt flags  : ");
				kull_m_dpapi_displayPromptFlags(pPrompt->dwPromptFlags);
				kprintf(L"\n");
			}
			else flags |= CRYPTPROTECT_UI_FORBIDDEN;
			if(entropy)
			{
				kprintf(L" > entropy       : ");
				kull_m_string_wprintf_hex(entropy, entropyLen, 0);
				kprintf(L"\n");
			}
			if(szPassword)
				kprintf(L" > password      : %s\n", szPassword);

			if(entry)
				status = kull_m_dpapi_unprotect_raw_or_blob(pDataIn, dwDataInLen, ppszDataDescr, (pOptionalEntropy && dwOptionalEntropyLen) ? pOptionalEntropy : entropy, (pOptionalEntropy && dwOptionalEntropyLen) ? dwOptionalEntropyLen : entropyLen, NULL, 0, pDataOut, dwDataOutLen, entry->data.keyHash, sizeof(entry->data.keyHash), szPassword);

			if(!status && ((masterkey && masterkeyLen) || isNormalAPI))
			{
				status = kull_m_dpapi_unprotect_raw_or_blob(pDataIn, dwDataInLen, ppszDataDescr, (pOptionalEntropy && dwOptionalEntropyLen) ? pOptionalEntropy : entropy, (pOptionalEntropy && dwOptionalEntropyLen) ? dwOptionalEntropyLen : entropyLen, pPrompt, flags, pDataOut, dwDataOutLen, masterkey, masterkeyLen, szPassword);
				if(status && masterkey && masterkeyLen)
					kuhl_m_dpapi_oe_masterkey_add(&blob->guidMasterKey, masterkey, masterkeyLen);

				if(!status && !masterkey)
				{
					if(GetLastError() == NTE_BAD_KEY_STATE)
					{
						PRINT_ERROR(L"NTE_BAD_KEY_STATE, needed Masterkey is: ");
						kull_m_string_displayGUID(&blob->guidMasterKey);
						kprintf(L"\n");
					}
					else PRINT_ERROR_AUTO(L"CryptUnprotectData");
				}
			}
			//kprintf(L"\n");
		}
		kull_m_dpapi_blob_delete(blob);
	}

	if(entropy)
		LocalFree(entropy);
	if(masterkey)
		LocalFree(masterkey);
	return status;
}