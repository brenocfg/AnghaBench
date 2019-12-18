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
struct TYPE_4__ {int valCount; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pszValue; TYPE_1__ AttrVal; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_2__* PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ kull_m_string_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BOOL kuhl_m_lsadump_dcshadow_encode_add_value(PCWSTR szValue, PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE pAttribute, BOOL fAddMultipleValues)
{
	DWORD dwNewCb = (fAddMultipleValues ? pAttribute->AttrVal.valCount+1 : 1);
	PWSTR* pszOldValues = pAttribute->pszValue;
	
	pAttribute->pszValue = (PWSTR *) LocalAlloc(LPTR, sizeof(PWSTR) * (dwNewCb));
	if(pAttribute->pszValue)
	{
		if(kull_m_string_copy(pAttribute->pszValue + dwNewCb-1, szValue))
		{
			if(fAddMultipleValues && pAttribute->AttrVal.valCount)
				RtlCopyMemory(pAttribute->pszValue, pszOldValues, sizeof(PWSTR) * pAttribute->AttrVal.valCount);
			pAttribute->AttrVal.valCount = dwNewCb;
			if(pszOldValues)
				LocalFree(pszOldValues);
			return TRUE;
		}
		else
			LocalFree(pAttribute->pszValue);
	}
	pAttribute->pszValue = pszOldValues;
	return FALSE;
}