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
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  guid; } ;
typedef  int /*<<< orphan*/  LPCGUID ;
typedef  size_t DWORD ;

/* Variables and functions */
 size_t ARRAYSIZE (TYPE_1__*) ; 
 TYPE_1__* KUHL_M_SYSENV_GUIDSTORE ; 
 scalar_t__ RtlEqualGuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ ) ; 

void kuhl_m_sysenv_display_vendorGuid(LPCGUID guid)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(KUHL_M_SYSENV_GUIDSTORE); i++)
	{
		if(RtlEqualGuid(guid, &KUHL_M_SYSENV_GUIDSTORE[i].guid))
		{
			kprintf(L"%s - ", KUHL_M_SYSENV_GUIDSTORE[i].name);
			break;
		}
	}
	kull_m_string_displayGUID(guid);
}