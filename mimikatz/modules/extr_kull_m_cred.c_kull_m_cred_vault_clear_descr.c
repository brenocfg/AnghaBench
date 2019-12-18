#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; TYPE_1__** entries; int /*<<< orphan*/  unk; int /*<<< orphan*/  version; } ;
struct TYPE_4__ {int id; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_2__* PKULL_M_CRED_VAULT_CLEAR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_printSuspectUnicodeString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_cred_vault_clear_descr(DWORD level, PKULL_M_CRED_VAULT_CLEAR clear)
{
	DWORD i;
	kprintf(L"%*s" L"**VAULT CREDENTIAL CLEAR ATTRIBUTES**\n", level << 1, L"");
	if(clear)
	{
		kprintf(L"%*s" L"  version: %08x - %u\n", level << 1, L"", clear->version, clear->version);
		kprintf(L"%*s" L"  count  : %08x - %u\n", level << 1, L"", clear->count, clear->count);
		kprintf(L"%*s" L"  unk    : %08x - %u\n", level << 1, L"", clear->unk, clear->unk);
		if(clear->entries)
		{
			kprintf(L"\n");
			for(i = 0; i < clear->count; i++)
			{
				kprintf(L"%*s" L"  * ", level << 1, L"");
				switch(clear->entries[i]->id)
				{
				case 1:
					kprintf(L"ressource     : ");
					break;
				case 2:
					kprintf(L"identity      : ");
					break;
				case 3:
					kprintf(L"authenticator : ");
					break;
				default:
					kprintf(L"property %3u  : ", clear->entries[i]->id);
					break;
				}
				kull_m_string_printSuspectUnicodeString(clear->entries[i]->data, clear->entries[i]->size);
				kprintf(L"\n");
			}
		}
	}
}