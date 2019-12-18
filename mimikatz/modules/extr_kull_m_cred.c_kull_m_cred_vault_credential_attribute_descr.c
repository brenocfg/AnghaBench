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
struct TYPE_3__ {scalar_t__ szData; scalar_t__ data; scalar_t__ szIV; scalar_t__ IV; int /*<<< orphan*/  unk2; int /*<<< orphan*/  unk1; int /*<<< orphan*/  unk0; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__* PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

void kull_m_cred_vault_credential_attribute_descr(DWORD level, PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE attribute)
{
	kprintf(L"%*s" L"**VAULT CREDENTIAL ATTRIBUTE**\n", level << 1, L"");
	if(attribute)
	{
		kprintf(L"%*s" L"  id      : %08x - %u\n", level << 1, L"", attribute->id, attribute->id);
		kprintf(L"%*s" L"  unk0/1/2: %08x/%08x/%08x\n", level << 1, L"", attribute->unk0, attribute->unk1, attribute->unk2);
		if(attribute->szIV && attribute->IV)
		{
			kprintf(L"%*s" L"  IV      : ", level << 1, L"");
			kull_m_string_wprintf_hex(attribute->IV, attribute->szIV, 0);
			kprintf(L"\n");
		}
		if(attribute->szData && attribute->data)
		{
			kprintf(L"%*s" L"  Data    : ", level << 1, L"");
			kull_m_string_wprintf_hex(attribute->data, attribute->szData, 0);
			kprintf(L"\n");
		}
	}
}