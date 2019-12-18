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
typedef  scalar_t__* LPBYTE ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  size_t DWORD ;
typedef  scalar_t__ BYTE ;
typedef  int BOOL ;

/* Variables and functions */
 size_t ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int SYSKEY_LENGTH ; 
 int TRUE ; 
 int /*<<< orphan*/ * kuhl_m_lsadump_SYSKEY_NAMES ; 
 size_t* kuhl_m_lsadump_SYSKEY_PERMUT ; 
 int /*<<< orphan*/  kull_m_registry_RegCloseKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_registry_RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_registry_RegQueryInfoKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int swscanf_s (int /*<<< orphan*/ *,char*,size_t*) ; 

BOOL kuhl_m_lsadump_getSyskey(PKULL_M_REGISTRY_HANDLE hRegistry, HKEY hLSA, LPBYTE sysKey)
{
	BOOL status = TRUE;
	DWORD i;
	HKEY hKey;
	wchar_t buffer[8 + 1];
	DWORD szBuffer;
	BYTE buffKey[SYSKEY_LENGTH];

	for(i = 0 ; (i < ARRAYSIZE(kuhl_m_lsadump_SYSKEY_NAMES)) && status; i++)
	{
		status = FALSE;
		if(kull_m_registry_RegOpenKeyEx(hRegistry, hLSA, kuhl_m_lsadump_SYSKEY_NAMES[i], 0, KEY_READ, &hKey))
		{
			szBuffer = 8 + 1;
			if(kull_m_registry_RegQueryInfoKey(hRegistry, hKey, buffer, &szBuffer, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
				status = swscanf_s(buffer, L"%x", (DWORD *) &buffKey[i*sizeof(DWORD)]) != -1;
			kull_m_registry_RegCloseKey(hRegistry, hKey);
		}
		else PRINT_ERROR(L"LSA Key Class read error\n");
	}
	
	if(status)
		for(i = 0; i < SYSKEY_LENGTH; i++)
			sysKey[i] = buffKey[kuhl_m_lsadump_SYSKEY_PERMUT[i]];	

	return status;
}