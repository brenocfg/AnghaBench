#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t USHORT ;
struct TYPE_4__ {int /*<<< orphan*/  KeyLength; scalar_t__ KeyOffset; int /*<<< orphan*/  KeyType; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PKERB_KEY_DATA ;
typedef  scalar_t__ PCWSTR ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  KERB_KEY_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_etype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

PKERB_KEY_DATA kuhl_m_lsadump_lsa_keyDataInfo(PVOID base, PKERB_KEY_DATA keys, USHORT Count, PCWSTR title)
{
	USHORT i;
	if(Count)
	{
		if(title)
			kprintf(L"    %s\n", title);
		for(i = 0; i < Count; i++)
		{
			kprintf(L"      %s : ", kuhl_m_kerberos_ticket_etype(keys[i].KeyType));
			kull_m_string_wprintf_hex((PBYTE) base + keys[i].KeyOffset, keys[i].KeyLength, 0);
			kprintf(L"\n");
		}
	}
	return (PKERB_KEY_DATA) ((PBYTE) keys + Count * sizeof(KERB_KEY_DATA));
}