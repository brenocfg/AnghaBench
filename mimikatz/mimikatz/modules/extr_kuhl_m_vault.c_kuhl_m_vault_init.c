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
typedef  scalar_t__ PVAULTOPENVAULT ;
typedef  scalar_t__ PVAULTGETITEM8 ;
typedef  scalar_t__ PVAULTGETITEM7 ;
typedef  scalar_t__ PVAULTGETINFORMATION ;
typedef  scalar_t__ PVAULTFREE ;
typedef  scalar_t__ PVAULTENUMERATEVAULTS ;
typedef  scalar_t__ PVAULTENUMERATEITEMTYPES ;
typedef  scalar_t__ PVAULTENUMERATEITEMS ;
typedef  scalar_t__ PVAULTCLOSEVAULT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LoadLibrary (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ VaultCloseVault ; 
 scalar_t__ VaultEnumerateItemTypes ; 
 scalar_t__ VaultEnumerateItems ; 
 scalar_t__ VaultEnumerateVaults ; 
 scalar_t__ VaultFree ; 
 scalar_t__ VaultGetInformation ; 
 scalar_t__ VaultGetItem7 ; 
 scalar_t__ VaultGetItem8 ; 
 scalar_t__ VaultOpenVault ; 
 int /*<<< orphan*/  hVaultCli ; 
 int isVaultInit ; 

NTSTATUS kuhl_m_vault_init()
{
	if(hVaultCli = LoadLibrary(L"vaultcli"))
	{
		VaultEnumerateItemTypes = (PVAULTENUMERATEITEMTYPES) GetProcAddress(hVaultCli, "VaultEnumerateItemTypes");
		VaultEnumerateVaults = (PVAULTENUMERATEVAULTS) GetProcAddress(hVaultCli, "VaultEnumerateVaults");
		VaultOpenVault = (PVAULTOPENVAULT) GetProcAddress(hVaultCli, "VaultOpenVault");
		VaultGetInformation = (PVAULTGETINFORMATION) GetProcAddress(hVaultCli, "VaultGetInformation");
		VaultEnumerateItems = (PVAULTENUMERATEITEMS) GetProcAddress(hVaultCli, "VaultEnumerateItems");
		VaultCloseVault = (PVAULTCLOSEVAULT) GetProcAddress(hVaultCli, "VaultCloseVault");
		VaultFree = (PVAULTFREE) GetProcAddress(hVaultCli, "VaultFree");
		VaultGetItem7 = (PVAULTGETITEM7) GetProcAddress(hVaultCli, "VaultGetItem");
		VaultGetItem8 = (PVAULTGETITEM8) VaultGetItem7;

		isVaultInit = VaultEnumerateItemTypes && VaultEnumerateVaults && VaultOpenVault && VaultGetInformation && VaultEnumerateItems && VaultCloseVault && VaultFree && VaultGetItem7;
	}
	return STATUS_SUCCESS;
}