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
struct TYPE_4__ {int /*<<< orphan*/  keyHash; int /*<<< orphan*/  guid; } ;
struct TYPE_5__ {TYPE_1__ data; } ;
typedef  TYPE_2__* PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void kuhl_m_dpapi_oe_masterkey_descr(PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY entry)
{
	if(entry)
	{
		kprintf(L"GUID:");
		kull_m_string_displayGUID(&entry->data.guid);
		kprintf(L";");
		
		kprintf(L"KeyHash:");
		kull_m_string_wprintf_hex(entry->data.keyHash, sizeof(entry->data.keyHash), 0);
		kprintf(L"\n");
	}
}