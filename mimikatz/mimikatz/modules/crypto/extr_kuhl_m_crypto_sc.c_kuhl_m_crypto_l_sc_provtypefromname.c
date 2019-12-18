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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CryptEnumProviders (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

DWORD kuhl_m_crypto_l_sc_provtypefromname(LPCWSTR szProvider)
{
	DWORD result = 0, provType, tailleRequise, index = 0;
	wchar_t * monProvider;
	for(index = 0, result = 0; !result && CryptEnumProviders(index, NULL, 0, &provType, NULL, &tailleRequise); index++)
	{
		if(monProvider = (wchar_t *) LocalAlloc(LPTR, tailleRequise))
		{
			if(CryptEnumProviders(index, NULL, 0, &provType, monProvider, &tailleRequise))
				if(_wcsicmp(szProvider, monProvider) == 0)
					result = provType;
			LocalFree(monProvider);
		}
	}
	if(!result && GetLastError() != ERROR_NO_MORE_ITEMS)
		PRINT_ERROR_AUTO(L"CryptEnumProviders");
	return provType;
}