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
#define  STYPE_DEVICE 131 
#define  STYPE_DISKTREE 130 
#define  STYPE_IPC 129 
 int STYPE_MASK ; 
#define  STYPE_PRINTQ 128 
 int STYPE_RESERVED_ALL ; 
 int STYPE_SPECIAL ; 
 int STYPE_TEMPORARY ; 
 int /*<<< orphan*/  kprintf (char*) ; 

void kuhl_m_net_share_type(DWORD type)
{
	switch(type & STYPE_MASK)
	{
	case STYPE_DISKTREE:
		kprintf(L"disktree ; ");
		break;
	case STYPE_PRINTQ:
		kprintf(L"printq ; ");
		break;
	case STYPE_DEVICE:
		kprintf(L"device ; ");
		break;
	case STYPE_IPC:
		kprintf(L"ipc ; ");
		break;
	}

	if(type & STYPE_TEMPORARY)
		kprintf(L"temporary ; ");
	if(type & STYPE_SPECIAL)
		kprintf(L"special ; ");
	if(type & STYPE_RESERVED_ALL)
		kprintf(L"reserved flag(s) ; ");
	kprintf(L"\n");
}