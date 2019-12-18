#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int valLen; int /*<<< orphan*/ * pVal; } ;
struct TYPE_5__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int LONGLONG ;
typedef  TYPE_1__ FILETIME ;
typedef  int DSTIME ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ATTRVAL ;

/* Variables and functions */
 scalar_t__ MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ kull_m_string_stringToFileTime (int /*<<< orphan*/ ,TYPE_1__*) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_date(ATTRVAL* pVal, PWSTR szValue)
{
	ULONG len = 0;
	FILETIME ft;
	DSTIME dstime;
	
	if(kull_m_string_stringToFileTime(szValue, &ft))
	{
		pVal->valLen = sizeof(DSTIME);
		pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
		dstime = ((LONGLONG)(ft.dwLowDateTime + ((LONGLONG)ft.dwHighDateTime << 32))) / 10000000;
		if(pVal->pVal)
			RtlCopyMemory(pVal->pVal, &dstime, sizeof(DSTIME));
	}
	else PRINT_ERROR_AUTO(L"kull_m_string_stringToFileTime");
	return pVal->pVal != NULL;
}