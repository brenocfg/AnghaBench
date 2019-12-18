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
typedef  int /*<<< orphan*/  PKULL_M_REGISTRY_HANDLE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/ * HKEY_USERS ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KEY_ENUMERATE_SUB_KEYS ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KULL_M_REGISTRY_TYPE_HIVE ; 
 int /*<<< orphan*/  KULL_M_REGISTRY_TYPE_OWN ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_ssh_keys4user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kull_m_registry_RegCloseKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegEnumKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ kull_m_registry_RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_registry_close (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_registry_open (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcsstr (int /*<<< orphan*/ *,char*) ; 

NTSTATUS kuhl_m_dpapi_ssh(int argc, wchar_t * argv[])
{
	PKULL_M_REGISTRY_HANDLE hRegistry;
	LPCWSTR szHive;
	HANDLE hHive;
	HKEY hBase, hUser;
	DWORD i, nbSubKeys, szMaxSubKeyLen, szKey;
	wchar_t * keyName;

	if(kull_m_string_args_byName(argc, argv, L"hive", &szHive, NULL))
	{
		hHive = CreateFile(szHive, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hHive != INVALID_HANDLE_VALUE)
		{
			if(kull_m_registry_open(KULL_M_REGISTRY_TYPE_HIVE, hHive, FALSE, &hRegistry))
			{
				kuhl_m_dpapi_ssh_keys4user(hRegistry, NULL, NULL, argc, argv);
				kull_m_registry_close(hRegistry);
			}
			CloseHandle(hHive);
		}
		else PRINT_ERROR_AUTO(L"CreateFile");
	}
	else
	{
		if(kull_m_registry_open(KULL_M_REGISTRY_TYPE_OWN, NULL, FALSE, &hRegistry))
		{
			if(kull_m_registry_RegOpenKeyEx(hRegistry, HKEY_USERS, NULL, 0, KEY_ENUMERATE_SUB_KEYS, &hBase))
			{
				if(kull_m_registry_RegQueryInfoKey(hRegistry, hBase, NULL, NULL, NULL, &nbSubKeys, &szMaxSubKeyLen, NULL, NULL, NULL, NULL, NULL, NULL))
				{
					szMaxSubKeyLen++;
					if(keyName = (wchar_t *) LocalAlloc(LPTR, (szMaxSubKeyLen + 1) * sizeof(wchar_t)))
					{
						for(i = 0; i < nbSubKeys; i++)
						{
							szKey = szMaxSubKeyLen;
							if(kull_m_registry_RegEnumKeyEx(hRegistry, hBase, i, keyName, &szKey, NULL, NULL, NULL, NULL))
							{
								if(!wcsstr(keyName, L"_Classes"))
								{
									kprintf(L"%s ", keyName);
									if(kull_m_registry_RegOpenKeyEx(hRegistry, hBase, keyName, 0, KEY_READ, &hUser))
									{
										kprintf(L"\n");
										kuhl_m_dpapi_ssh_keys4user(hRegistry, hUser, keyName, argc, argv);
										kull_m_registry_RegCloseKey(hRegistry, hUser);
									}
									else PRINT_ERROR_AUTO(L"kull_m_registry_RegOpenKeyEx");
								}
							}
						}
						LocalFree(keyName);
					}
				}
				kull_m_registry_RegCloseKey(hRegistry, hBase);
			}
			else PRINT_ERROR_AUTO(L"kull_m_registry_RegOpenKeyEx");
			kull_m_registry_close(hRegistry);
		}
	}
	return STATUS_SUCCESS;
}