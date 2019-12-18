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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_3__ {int /*<<< orphan*/ * pVal; int /*<<< orphan*/  valLen; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ATTRVAL ;

/* Variables and functions */
 scalar_t__ ConvertStringSecurityDescriptorToSecurityDescriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 scalar_t__ MIDL_user_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDDL_REVISION_1 ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_security_descriptor(ATTRVAL* pVal, PWSTR szValue)
{
	ULONG len = 0;
	PSECURITY_DESCRIPTOR sddl = NULL;
	
	if(ConvertStringSecurityDescriptorToSecurityDescriptor(szValue, SDDL_REVISION_1, &sddl, &len))
	{
		pVal->valLen = len;
		pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
		if(pVal->pVal)
			RtlCopyMemory(pVal->pVal, sddl, pVal->valLen);
		LocalFree(sddl);
	}
	else PRINT_ERROR_AUTO(L"ConvertStringSecurityDescriptorToSecurityDescriptor");
	return pVal->pVal != NULL;
}