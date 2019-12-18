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
struct TYPE_3__ {int __dwKeyLen; int /*<<< orphan*/  pbKey; int /*<<< orphan*/  algCrypt; int /*<<< orphan*/  algHash; int /*<<< orphan*/  rounds; int /*<<< orphan*/  salt; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__* PKULL_M_DPAPI_MASTERKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_crypto_algid_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void kull_m_dpapi_masterkey_descr(DWORD level, PKULL_M_DPAPI_MASTERKEY masterkey)
{
	kprintf(L"%*s" L"**MASTERKEY**\n", level << 1, L"");
	if(masterkey)
	{
		kprintf(L"%*s" L"  dwVersion        : %08x - %u\n", level << 1, L"", masterkey->dwVersion, masterkey->dwVersion);
		kprintf(L"%*s" L"  salt             : ", level << 1, L""); kull_m_string_wprintf_hex(masterkey->salt, sizeof(masterkey->salt), 0); kprintf(L"\n");
		kprintf(L"%*s" L"  rounds           : %08x - %u\n", level << 1, L"", masterkey->rounds, masterkey->rounds);
		kprintf(L"%*s" L"  algHash          : %08x - %u (%s)\n", level << 1, L"", masterkey->algHash, masterkey->algHash, kull_m_crypto_algid_to_name(masterkey->algHash));
		kprintf(L"%*s" L"  algCrypt         : %08x - %u (%s)\n", level << 1, L"", masterkey->algCrypt, masterkey->algCrypt, kull_m_crypto_algid_to_name(masterkey->algCrypt));
		kprintf(L"%*s" L"  pbKey            : ", level << 1, L""); kull_m_string_wprintf_hex(masterkey->pbKey, masterkey->__dwKeyLen, 0); kprintf(L"\n\n");
	}
}