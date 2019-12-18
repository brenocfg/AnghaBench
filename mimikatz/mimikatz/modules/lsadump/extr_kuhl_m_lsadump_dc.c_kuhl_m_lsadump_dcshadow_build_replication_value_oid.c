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
struct TYPE_3__ {int valLen; scalar_t__ pVal; } ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  scalar_t__ PSTR ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ATTRVAL ;
typedef  int /*<<< orphan*/  ATTRTYP ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ MIDL_user_allocate (int) ; 
 int /*<<< orphan*/  SCHEMA_DEFAULT_PREFIX_TABLE ; 
 int /*<<< orphan*/  kull_m_rpc_drsr_MakeAttid (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_string_unicode_to_ansi (int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_oid(ATTRVAL* pVal, PWSTR szValue)
{
	BOOL fSuccess = FALSE;
	PSTR szANSIValue = kull_m_string_unicode_to_ansi(szValue);
	
	if(szANSIValue)
	{
		pVal->valLen = sizeof(DWORD);
		pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
		if(pVal->pVal)
			fSuccess = kull_m_rpc_drsr_MakeAttid((SCHEMA_PREFIX_TABLE*) &SCHEMA_DEFAULT_PREFIX_TABLE, szANSIValue, (ATTRTYP*) pVal->pVal, FALSE );
		LocalFree(szANSIValue);
	}
	return fSuccess;
}