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
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CertEnumSystemStore (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_stores_enumCallback_print ; 
 int /*<<< orphan*/  kull_m_crypto_system_store_to_dword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ *,char*) ; 

NTSTATUS kuhl_m_crypto_l_stores(int argc, wchar_t * argv[])
{
	DWORD dwSystemStore, nbStore = 0;
	PCWCHAR szSystemStore;
	kull_m_string_args_byName(argc, argv, L"systemstore", &szSystemStore, L"CURRENT_USER"/*kuhl_m_crypto_system_stores[0].name*/);
	dwSystemStore = kull_m_crypto_system_store_to_dword(szSystemStore);
	kprintf(L"Asking for System Store \'%s\' (0x%08x)\n", szSystemStore, dwSystemStore);

	if(!CertEnumSystemStore(dwSystemStore, NULL, &nbStore, kuhl_m_crypto_l_stores_enumCallback_print))
		PRINT_ERROR_AUTO(L"CertEnumSystemStore");

	return STATUS_SUCCESS;
}