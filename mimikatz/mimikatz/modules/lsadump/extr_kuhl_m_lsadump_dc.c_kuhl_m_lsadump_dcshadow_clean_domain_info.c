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
struct TYPE_3__ {scalar_t__ request; scalar_t__ ld; scalar_t__ hGetNCChangeCalled; scalar_t__ szDsServiceName; scalar_t__ szConfigurationNamingContext; scalar_t__ szDCDsServiceName; scalar_t__ szDomainNamingContext; scalar_t__ szDomainName; } ;
typedef  TYPE_1__* PDCSHADOW_DOMAIN_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_clean_push_request (scalar_t__) ; 
 int /*<<< orphan*/  ldap_unbind (scalar_t__) ; 

void kuhl_m_lsadump_dcshadow_clean_domain_info(PDCSHADOW_DOMAIN_INFO info)
{
	if(info->szDomainName)
		LocalFree(info->szDomainName);
	if(info->szDomainNamingContext)
		LocalFree(info->szDomainNamingContext);
	if(info->szDCDsServiceName)
		LocalFree(info->szDCDsServiceName);
	if(info->szConfigurationNamingContext)
		LocalFree(info->szConfigurationNamingContext);
	if(info->szDsServiceName)
		LocalFree(info->szDsServiceName);
	if(info->hGetNCChangeCalled)
		CloseHandle(info->hGetNCChangeCalled);
	if(info->ld)
		ldap_unbind(info->ld);
	if(info->request)
		kuhl_m_lsadump_dcshadow_clean_push_request(info->request);
}