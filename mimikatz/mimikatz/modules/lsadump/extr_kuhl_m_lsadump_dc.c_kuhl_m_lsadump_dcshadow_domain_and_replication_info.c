#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  InvocationId; int /*<<< orphan*/  InstanceId; } ;
struct TYPE_10__ {int /*<<< orphan*/ * request; int /*<<< orphan*/  szFakeFQDN; TYPE_3__ mimiDc; TYPE_3__ realDc; int /*<<< orphan*/  szDCFQDN; int /*<<< orphan*/  fUseSchemaSignature; } ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DCSHADOW_DOMAIN_DC_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_3__*,int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int kuhl_m_lsadump_dcshadow_build_replication (TYPE_1__*) ; 
 int kuhl_m_lsadump_dcshadow_domaininfo_computer (TYPE_1__*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_domaininfo_rootDse (TYPE_1__*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_domaininfo_schemasignature (TYPE_1__*) ; 
 int kuhl_m_lsadump_dcshadow_objectGUID_invocationGUID (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 

BOOL kuhl_m_lsadump_dcshadow_domain_and_replication_info(PDCSHADOW_DOMAIN_INFO info)
{
	BOOL fSuccess = FALSE;
	DWORD dwErr = 0;

	kprintf(L"** Domain Info **\n\n");
	fSuccess = kuhl_m_lsadump_dcshadow_domaininfo_rootDse(info)
		&& (!info->fUseSchemaSignature || kuhl_m_lsadump_dcshadow_domaininfo_schemasignature(info));
	if(fSuccess)
	{
		fSuccess = kuhl_m_lsadump_dcshadow_domaininfo_computer(info);
	}
	kprintf(L"\n");
	if(fSuccess)
	{
		kprintf(L"** Server Info **\n\n");
		if(fSuccess = kuhl_m_lsadump_dcshadow_objectGUID_invocationGUID(info, info->szDCFQDN, &info->realDc))
		{
			kprintf(L"Server: %s\n  InstanceId  : ", info->szDCFQDN);
			kull_m_string_displayGUID(&info->realDc.InstanceId);
			kprintf(L"\n  InvocationId: ");
			kull_m_string_displayGUID(&info->realDc.InvocationId);
			kprintf(L"\n");
		}
		RtlZeroMemory(&info->mimiDc, sizeof(DCSHADOW_DOMAIN_DC_INFO));
		if(kuhl_m_lsadump_dcshadow_objectGUID_invocationGUID(info, info->szFakeFQDN, &info->mimiDc))
		{
			kprintf(L"Fake Server (already registered): %s\n  InstanceId  : ", info->szFakeFQDN);
			kull_m_string_displayGUID(&info->mimiDc.InstanceId);
			kprintf(L"\n  InvocationId: ");
			kull_m_string_displayGUID(&info->mimiDc.InvocationId);
			kprintf(L"\n");
		}
		else kprintf(L"Fake Server (not already registered): %s\n", info->szFakeFQDN);
		kprintf(L"\n");
	}
	if(fSuccess && info->request != NULL)
		fSuccess = kuhl_m_lsadump_dcshadow_build_replication(info);
	return fSuccess;
}