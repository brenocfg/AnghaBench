#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int valLen; int /*<<< orphan*/ * pVal; } ;
struct TYPE_4__ {int structLen; int NameLen; int /*<<< orphan*/  StringName; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int DWORD ;
typedef  TYPE_1__ DSNAME ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ATTRVAL ;

/* Variables and functions */
 scalar_t__ MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (int /*<<< orphan*/ *,int) ; 
 int lstrlen (int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_dn(ATTRVAL* pVal, PWSTR szValue)
{
	DWORD len = lstrlen(szValue);
	
	pVal->valLen = sizeof(DSNAME) + len * sizeof(WCHAR);
	pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
	if(pVal->pVal)
	{
		RtlZeroMemory(pVal->pVal, pVal->valLen);
		((DSNAME*)pVal->pVal)->structLen = pVal->valLen;
		((DSNAME*)pVal->pVal)->NameLen = len;
		RtlCopyMemory(((DSNAME*)pVal->pVal)->StringName, szValue, (len+1)*sizeof(WCHAR));
	}
	return pVal->pVal != NULL;
}