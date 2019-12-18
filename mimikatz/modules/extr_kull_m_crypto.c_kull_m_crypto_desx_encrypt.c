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
typedef  scalar_t__ PVOID ;
typedef  int /*<<< orphan*/ * PULONGLONG ;
typedef  scalar_t__ PBYTE ;
typedef  scalar_t__ LPCVOID ;
typedef  int /*<<< orphan*/  HCRYPTPROV ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_DES ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int) ; 
 scalar_t__ kull_m_crypto_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_crypto_desx_encrypt(HCRYPTPROV hProv, LPCVOID key, LPCVOID block, PVOID encrypted)
{
	BOOL status = FALSE;
	HCRYPTKEY hKey;
	DWORD dwLen = 8;
	RtlCopyMemory(encrypted, block, 8);
	if(kull_m_crypto_hkey(hProv, CALG_DES, key, 8, 0, &hKey, NULL))
	{
		*(PULONGLONG) encrypted ^= *(PULONGLONG) ((PBYTE) key + 8);
		if(status = CryptEncrypt(hKey, 0, FALSE, 0, (PBYTE) encrypted, &dwLen, dwLen))
			*(PULONGLONG) encrypted ^= *(PULONGLONG)  ((PBYTE) key + 16);
		CryptDestroyKey(hKey);
	}
	return status;
}