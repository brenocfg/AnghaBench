#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  isInstanceId; } ;
struct TYPE_7__ {TYPE_6__ mimiDc; int /*<<< orphan*/  szFakeFQDN; } ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_objectGUID_invocationGUID (TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_register_NTDSA (TYPE_1__*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_register_ldap (TYPE_1__*) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_register(PDCSHADOW_DOMAIN_INFO info)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	
	if(!info->mimiDc.isInstanceId)
	{
		if(kuhl_m_lsadump_dcshadow_register_ldap(info))
		{
			if(NT_SUCCESS(kuhl_m_lsadump_dcshadow_register_NTDSA(info)))
			{
				if(kuhl_m_lsadump_dcshadow_objectGUID_invocationGUID(info, info->szFakeFQDN, &info->mimiDc))
					status = STATUS_SUCCESS;
				else PRINT_ERROR(L"Unable to get invocation Id\n");
			}
			else PRINT_ERROR(L"Unable to add object via Drs\n");
		}
	}
	else
	{
		kprintf(L"Already registered\n");
		status = STATUS_SUCCESS;
	}
	return status;
}