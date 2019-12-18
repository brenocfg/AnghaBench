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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int USHORT ;
struct TYPE_5__ {int member_0; int member_1; char* member_2; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_6__ {int valLen; void* pVal; } ;
typedef  char* PWSTR ;
typedef  void* PBYTE ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ATTRVAL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ MIDL_user_allocate (int) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  RtlCopyMemory (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlGUIDFromString (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_string_stringToHex (char*,void*,int) ; 
 int lstrlen (char*) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_octet_string(ATTRVAL* pVal, PWSTR szValue)
{
	DWORD len = lstrlen(szValue);
	
	if(len == 38 && szValue[0] == '{' && szValue[37] == '}')
	{
		GUID guid;
		UNICODE_STRING GuidString = {(USHORT)len*sizeof(WCHAR),(USHORT)len*sizeof(WCHAR), szValue};
		if(NT_SUCCESS(RtlGUIDFromString(&GuidString, &guid)))
		{
			pVal->valLen = sizeof(GUID);
			pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
			if(!pVal->pVal)
				return FALSE;
			RtlCopyMemory(pVal->pVal, &guid, sizeof(GUID));
			return TRUE;
		}
		else PRINT_ERROR(L"RtlGUIDFromString %s\n", szValue);

	}
	else
	{
		pVal->valLen = (ULONG) (len/2);
		pVal->pVal = (PBYTE) MIDL_user_allocate(pVal->valLen);
		if(!pVal->pVal)
			return FALSE;
		if(kull_m_string_stringToHex(szValue, pVal->pVal, pVal->valLen))
			return TRUE;
		PRINT_ERROR_AUTO(L"kull_m_string_stringToHex");
	}
	return FALSE;
}