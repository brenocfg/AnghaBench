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
struct TYPE_3__ {int valLen; int /*<<< orphan*/ * pVal; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ATTRVAL ;

/* Variables and functions */
 scalar_t__ MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_dword(ATTRVAL* pVal, PWSTR szValue)
{
	
	pVal->valLen = sizeof(DWORD);
	pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
	if(pVal->pVal)
		*(PDWORD) pVal->pVal = wcstoul(szValue, NULL, 10);
	return pVal->pVal != NULL;
}