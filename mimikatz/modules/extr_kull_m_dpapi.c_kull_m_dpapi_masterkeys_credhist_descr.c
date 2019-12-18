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
struct TYPE_3__ {int /*<<< orphan*/  guid; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__* PKULL_M_DPAPI_MASTERKEY_CREDHIST ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 

void kull_m_dpapi_masterkeys_credhist_descr(DWORD level, PKULL_M_DPAPI_MASTERKEY_CREDHIST credhist)
{
	kprintf(L"%*s" L"**CREDHIST INFO**\n", level << 1, L"");
	if(credhist)
	{
		kprintf(L"%*s" L"  dwVersion        : %08x - %u\n", level << 1, L"", credhist->dwVersion, credhist->dwVersion);
		kprintf(L"%*s" L"  guid             : ", level << 1, L""); kull_m_string_displayGUID(&credhist->guid); kprintf(L"\n\n");
	}
}