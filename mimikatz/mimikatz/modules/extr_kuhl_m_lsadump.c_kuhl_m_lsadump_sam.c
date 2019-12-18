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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  KULL_M_REGISTRY_TYPE_HIVE ; 
 int /*<<< orphan*/  KULL_M_REGISTRY_TYPE_OWN ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int SYSKEY_LENGTH ; 
 scalar_t__ kuhl_m_lsadump_getComputerAndSyskey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_getUsersAndSamKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_registry_RegCloseKey (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kull_m_registry_close (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_registry_open (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_lsadump_sam(int argc, wchar_t * argv[])
{
	HANDLE hDataSystem, hDataSam;
	PKULL_M_REGISTRY_HANDLE hRegistry, hRegistry2;
	HKEY hBase;
	BYTE sysKey[SYSKEY_LENGTH];
	LPCWSTR szSystem = NULL, szSam = NULL;

	if(kull_m_string_args_byName(argc, argv, L"system", &szSystem, NULL))
	{
		hDataSystem = CreateFile(szSystem, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if(hDataSystem != INVALID_HANDLE_VALUE)
		{
			if(kull_m_registry_open(KULL_M_REGISTRY_TYPE_HIVE, hDataSystem, FALSE, &hRegistry))
			{
				if(kuhl_m_lsadump_getComputerAndSyskey(hRegistry, NULL, sysKey))
				{
					if(kull_m_string_args_byName(argc, argv, L"sam", &szSam, NULL))
					{
						hDataSam = CreateFile(szSam, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
						if(hDataSam != INVALID_HANDLE_VALUE)
						{
							if(kull_m_registry_open(KULL_M_REGISTRY_TYPE_HIVE, hDataSam, FALSE, &hRegistry2))
							{
								kuhl_m_lsadump_getUsersAndSamKey(hRegistry2, NULL, sysKey);
								kull_m_registry_close(hRegistry2);
							}
							CloseHandle(hDataSam);
						}
						else PRINT_ERROR_AUTO(L"CreateFile (SAM hive)");
					}
				}
				kull_m_registry_close(hRegistry);
			}
			CloseHandle(hDataSystem);
		}
		else PRINT_ERROR_AUTO(L"CreateFile (SYSTEM hive)");
	}
	else
	{
		if(kull_m_registry_open(KULL_M_REGISTRY_TYPE_OWN, NULL, FALSE, &hRegistry))
		{
			if(kull_m_registry_RegOpenKeyEx(hRegistry, HKEY_LOCAL_MACHINE, L"SYSTEM", 0, KEY_READ, &hBase))
			{
				if(kuhl_m_lsadump_getComputerAndSyskey(hRegistry, hBase, sysKey))
				{
					if(kull_m_registry_RegOpenKeyEx(hRegistry, HKEY_LOCAL_MACHINE, L"SAM", 0, KEY_READ, &hBase))
					{
						kuhl_m_lsadump_getUsersAndSamKey(hRegistry, hBase, sysKey);
						kull_m_registry_RegCloseKey(hRegistry, hBase);
					}
					else PRINT_ERROR_AUTO(L"kull_m_registry_RegOpenKeyEx (SAM)");
				}
				kull_m_registry_RegCloseKey(hRegistry, hBase);
			}
			kull_m_registry_close(hRegistry);
		}
	}
	return STATUS_SUCCESS;
}