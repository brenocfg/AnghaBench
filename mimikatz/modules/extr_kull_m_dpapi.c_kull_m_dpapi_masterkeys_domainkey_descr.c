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
struct TYPE_3__ {int /*<<< orphan*/  dwAccesscheckLen; int /*<<< orphan*/  pbAccesscheck; int /*<<< orphan*/  dwSecretLen; int /*<<< orphan*/  pbSecret; int /*<<< orphan*/  guidMasterKey; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__* PKULL_M_DPAPI_MASTERKEY_DOMAINKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_dpapi_masterkeys_domainkey_descr(DWORD level, PKULL_M_DPAPI_MASTERKEY_DOMAINKEY domainkey)
{
	kprintf(L"%*s" L"**DOMAINKEY**\n", level << 1, L"");
	if(domainkey)
	{
		kprintf(L"%*s" L"  dwVersion        : %08x - %u\n", level << 1, L"", domainkey->dwVersion, domainkey->dwVersion);
		kprintf(L"%*s" L"  dwSecretLen      : %08x - %u\n", level << 1, L"", domainkey->dwSecretLen, domainkey->dwSecretLen);
		kprintf(L"%*s" L"  dwAccesscheckLen : %08x - %u\n", level << 1, L"", domainkey->dwAccesscheckLen, domainkey->dwAccesscheckLen);
		kprintf(L"%*s" L"  guidMasterKey    : ", level << 1, L""); kull_m_string_displayGUID(&domainkey->guidMasterKey); kprintf(L"\n");
		kprintf(L"%*s" L"  pbSecret         : ", level << 1, L""); kull_m_string_wprintf_hex(domainkey->pbSecret, domainkey->dwSecretLen, 0); kprintf(L"\n");
		kprintf(L"%*s" L"  pbAccesscheck    : ", level << 1, L""); kull_m_string_wprintf_hex(domainkey->pbAccesscheck, domainkey->dwAccesscheckLen, 0); kprintf(L"\n\n");
	}
}