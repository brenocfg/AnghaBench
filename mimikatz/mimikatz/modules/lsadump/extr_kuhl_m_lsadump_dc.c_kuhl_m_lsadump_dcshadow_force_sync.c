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
struct TYPE_4__ {int dwPushFlags; int /*<<< orphan*/  szSchemaNamingContext; int /*<<< orphan*/  szConfigurationNamingContext; int /*<<< orphan*/  szDomainNamingContext; } ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  DRS_HANDLE ;

/* Variables and functions */
 int DOMAIN_INFO_PUSH_FLAGS_CONFIG ; 
 int DOMAIN_INFO_PUSH_FLAGS_ROOT ; 
 int DOMAIN_INFO_PUSH_FLAGS_SCHEMA ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_force_sync_partition (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_force_sync(PDCSHADOW_DOMAIN_INFO info, DRS_HANDLE hDrs)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	
	if(info->dwPushFlags & DOMAIN_INFO_PUSH_FLAGS_ROOT)
	{
		status = kuhl_m_lsadump_dcshadow_force_sync_partition(info, hDrs, info->szDomainNamingContext);
		if(!NT_SUCCESS(status))
			return status;
	}
	if(info->dwPushFlags & DOMAIN_INFO_PUSH_FLAGS_CONFIG)
	{
		status = kuhl_m_lsadump_dcshadow_force_sync_partition(info, hDrs, info->szConfigurationNamingContext);
		if(!NT_SUCCESS(status))
			return status;
	}
	if(info->dwPushFlags & DOMAIN_INFO_PUSH_FLAGS_SCHEMA)
	{
		status = kuhl_m_lsadump_dcshadow_force_sync_partition(info, hDrs, info->szSchemaNamingContext);
		if(!NT_SUCCESS(status))
			return status;
	}
	return status;
}