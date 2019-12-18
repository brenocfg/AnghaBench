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
struct TYPE_3__ {int /*<<< orphan*/ * pVal; int /*<<< orphan*/  valLen; } ;
typedef  scalar_t__ PWSTR ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ATTRVAL ;

/* Variables and functions */
 scalar_t__ ConvertStringSidToSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLengthSid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 scalar_t__ MIDL_user_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_sid(ATTRVAL* pVal, PWSTR szValue)
{
	PSID pSid;
	pVal->pVal = NULL;
	if(ConvertStringSidToSid((PCWSTR) szValue, &pSid))
	{
		pVal->valLen = GetLengthSid(pSid);
		if(pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen))
			RtlCopyMemory(pVal->pVal, pSid, pVal->valLen);
		else PRINT_ERROR_AUTO(L"LocalAlloc");
		LocalFree(pSid);
	}
	else PRINT_ERROR_AUTO(L"ConvertStringSidToSid");
	return pVal->pVal != NULL;
}