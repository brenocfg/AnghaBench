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
typedef  scalar_t__ PSTR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_DELETEKEYSET ; 
 int /*<<< orphan*/  CryptAcquireContextA (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGetProvParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  PP_CONTAINER ; 
 int /*<<< orphan*/  PP_NAME ; 
 int /*<<< orphan*/  PP_PROVTYPE ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 

BOOL kull_m_crypto_close_hprov_delete_container(HCRYPTPROV hProv)
{
	BOOL status = FALSE;
	DWORD provtype, szLen = 0;
	PSTR container, provider;
	if(CryptGetProvParam(hProv, PP_CONTAINER, NULL, &szLen, 0))
	{
		if(container = (PSTR) LocalAlloc(LPTR, szLen))
		{
			if(CryptGetProvParam(hProv, PP_CONTAINER, (LPBYTE) container, &szLen, 0))
			{
				if(CryptGetProvParam(hProv, PP_NAME, NULL, &szLen, 0))
				{
					if(provider = (PSTR) LocalAlloc(LPTR, szLen))
					{
						if(CryptGetProvParam(hProv, PP_NAME, (LPBYTE) provider, &szLen, 0))
						{
							szLen = sizeof(DWORD);
							if(CryptGetProvParam(hProv, PP_PROVTYPE, (LPBYTE) &provtype, &szLen, 0))
							{
								CryptReleaseContext(hProv, 0);
								status = CryptAcquireContextA(&hProv, container, provider, provtype, CRYPT_DELETEKEYSET);
							}
						}
						LocalFree(provider);
					}
				}
				LocalFree(container);
			}
		}
	}
	if(!status)
		PRINT_ERROR_AUTO(L"CryptGetProvParam/CryptAcquireContextA");
	return status;
}