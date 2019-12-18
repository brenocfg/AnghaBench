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
struct TYPE_3__ {scalar_t__ key; int /*<<< orphan*/  unk2; int /*<<< orphan*/  unk1; int /*<<< orphan*/  unk0; int /*<<< orphan*/  Name; int /*<<< orphan*/  vault; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__* PKULL_M_CRED_VAULT_POLICY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_cred_vault_policy_key_descr (int,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 

void kull_m_cred_vault_policy_descr(DWORD level, PKULL_M_CRED_VAULT_POLICY policy)
{
	kprintf(L"%*s" L"**VAULT POLICY**\n", level << 1, L"");
	if(policy)
	{
		kprintf(L"%*s" L"  version : %08x - %u\n", level << 1, L"", policy->version, policy->version);
		kprintf(L"%*s" L"  vault   : ", level << 1, L""); kull_m_string_displayGUID(&policy->vault); kprintf(L"\n");
		kprintf(L"%*s" L"  Name    : %s\n", level << 1, L"", policy->Name);
		kprintf(L"%*s" L"  unk0/1/2: %08x/%08x/%08x\n", level << 1, L"", policy->unk0, policy->unk1, policy->unk2);
		if(policy->key)
			kull_m_cred_vault_policy_key_descr(level + 1, policy->key);
		kprintf(L"\n");
	}
}