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
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PPOLICY_DNS_DOMAIN_INFO ;
typedef  TYPE_1__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LsaClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaOpenPolicy (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaQueryInformationPolicy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLICY_VIEW_LOCAL_INFORMATION ; 
 int /*<<< orphan*/  PolicyDnsDomainInformation ; 

BOOL kull_m_net_getCurrentDomainInfo(PPOLICY_DNS_DOMAIN_INFO * pDomainInfo)
{
	BOOL status = FALSE;
	LSA_HANDLE hLSA;
	LSA_OBJECT_ATTRIBUTES oaLsa = {0};

	if(NT_SUCCESS(LsaOpenPolicy(NULL, &oaLsa, POLICY_VIEW_LOCAL_INFORMATION, &hLSA)))
	{
		status = NT_SUCCESS(LsaQueryInformationPolicy(hLSA, PolicyDnsDomainInformation, (PVOID *) pDomainInfo));
		LsaClose(hLSA);
	}
	return status;
}