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
typedef  char* PCWCHAR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CRYPT_MACHINE_KEYSET ; 
 int CRYPT_SILENT ; 
 char* MS_KEY_STORAGE_PROVIDER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_keys_capi (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kuhl_m_crypto_l_keys_cng (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,char*) ; 
 char* kull_m_crypto_provider_to_realname (char*) ; 
 int kull_m_crypto_provider_type_to_dword (char*) ; 
 int /*<<< orphan*/  kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,char**,char*) ; 
 int wcstoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_crypto_l_keys(int argc, wchar_t * argv[])
{
	PCWCHAR szProvider, pProvider, szProviderType, szStore, szCngProvider;
	DWORD dwProviderType, dwFlags = 0;
	
	BOOL export = kull_m_string_args_byName(argc, argv, L"export", NULL, NULL);
	
	kull_m_string_args_byName(argc, argv, L"provider", &szProvider, L"MS_ENHANCED_PROV");
	if(!(pProvider = kull_m_crypto_provider_to_realname(szProvider)))
		pProvider = szProvider;
	
	kull_m_string_args_byName(argc, argv, L"providertype", &szProviderType, L"PROV_RSA_FULL");
	if(!(dwProviderType = kull_m_crypto_provider_type_to_dword(szProviderType)))
		dwProviderType = wcstoul(szProviderType, NULL, 0);

	if(kull_m_string_args_byName(argc, argv, L"machine", NULL, NULL))
		dwFlags = CRYPT_MACHINE_KEYSET; // same as NCRYPT_MACHINE_KEY_FLAG :)
	szStore = dwFlags ? L"machine" : L"user";
	
	if(kull_m_string_args_byName(argc, argv, L"silent", NULL, NULL))
		dwFlags |= CRYPT_SILENT;

	kull_m_string_args_byName(argc, argv, L"cngprovider", &szCngProvider, MS_KEY_STORAGE_PROVIDER);

	kprintf(L" * Store         : \'%s\'\n"	
			L" * Provider      : \'%s\' (\'%s\')\n"
			L" * Provider type : \'%s\' (%u)\n"
			L" * CNG Provider  : \'%s\'\n",
			szStore,
			szProvider, pProvider,
			szProviderType, dwProviderType,
			szCngProvider);

	kprintf(L"\nCryptoAPI keys :\n");
	kuhl_m_crypto_l_keys_capi(NULL, pProvider, dwProviderType, dwFlags, export, szStore);
	kprintf(L"\nCNG keys :\n");
	kuhl_m_crypto_l_keys_cng(NULL, szCngProvider, dwFlags, export, szStore);
	return STATUS_SUCCESS;
}