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
 int ARRAYSIZE (char**) ; 
 int CRYPTPROTECT_SYSTEM ; 
 char** DPAPIProtectFlagsToStrings ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 

void kull_m_dpapi_displayProtectionFlags(DWORD flags)
{
	DWORD i;
	for(i = 0; i < ARRAYSIZE(DPAPIProtectFlagsToStrings); i++)
		if((flags >> i) & 1)
			kprintf(L"%s ; ", DPAPIProtectFlagsToStrings[i]);
	if(flags & CRYPTPROTECT_SYSTEM)
		kprintf(L"%s ; ", L"system");
}