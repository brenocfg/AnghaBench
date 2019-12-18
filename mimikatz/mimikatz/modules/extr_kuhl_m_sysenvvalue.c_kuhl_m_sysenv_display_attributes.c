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
typedef  int DWORD ;

/* Variables and functions */
 int ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * KUHL_M_SYSENV_ATTRIBUTES ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 

void kuhl_m_sysenv_display_attributes(DWORD attributes)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(KUHL_M_SYSENV_ATTRIBUTES); i++)
		if((1 << i) & attributes)
			kprintf(L"%s, ", KUHL_M_SYSENV_ATTRIBUTES[i]);
}