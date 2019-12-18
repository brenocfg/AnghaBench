#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_13__ {char* szAttributeName; int /*<<< orphan*/  fIsSensitive; } ;
struct TYPE_12__ {size_t cNumAttributes; size_t cNumObjects; TYPE_4__* pAttributes; TYPE_2__* pObjects; } ;
struct TYPE_11__ {size_t cbAttributes; TYPE_1__* pAttributes; } ;
struct TYPE_10__ {TYPE_4__* pAttribute; } ;
typedef  TYPE_3__* PDCSHADOW_PUSH_REQUEST ;
typedef  TYPE_4__* PDCSHADOW_OBJECT_ATTRIBUTE ;
typedef  char* PCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  DCSHADOW_OBJECT_ATTRIBUTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (TYPE_4__*) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_4__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsicmp (char*,char*) ; 
 int /*<<< orphan*/  kull_m_string_copy (char**,char*) ; 

BOOL kuhl_m_lsadump_dcshadow_encode_attribute(PDCSHADOW_PUSH_REQUEST request, PCWSTR szAttribute, PDCSHADOW_OBJECT_ATTRIBUTE *pProperty)
{
	DWORD i, j;
	PDCSHADOW_OBJECT_ATTRIBUTE oldAttributes;
	ULONG_PTR pt_dif;

	for(i = 0; i < request->cNumAttributes; i++)
	{
		if(!_wcsicmp(request->pAttributes[i].szAttributeName, szAttribute))
		{
			*pProperty = request->pAttributes + i;
			return TRUE;
		}
	}

	oldAttributes = request->pAttributes;
	request->pAttributes = (PDCSHADOW_OBJECT_ATTRIBUTE) LocalAlloc(LPTR, sizeof(DCSHADOW_OBJECT_ATTRIBUTE) * (request->cNumAttributes+1));
	if(!request->pAttributes)
	{
		request->pAttributes = oldAttributes;
		return FALSE;
	}
	RtlCopyMemory(request->pAttributes, oldAttributes, sizeof(DCSHADOW_OBJECT_ATTRIBUTE) * request->cNumAttributes);
	if(oldAttributes)
		LocalFree(oldAttributes);
	pt_dif = (ULONG_PTR) request->pAttributes - (ULONG_PTR) oldAttributes;
	for(i = 0; i < request->cNumObjects; i++)
		for(j = 0; j < request->pObjects[i].cbAttributes; j++)
			request->pObjects[i].pAttributes[j].pAttribute = (PDCSHADOW_OBJECT_ATTRIBUTE) ((ULONG_PTR) request->pObjects[i].pAttributes[j].pAttribute + pt_dif);
	*pProperty = request->pAttributes + request->cNumAttributes;

	if(!kull_m_string_copy(&((*pProperty)->szAttributeName), szAttribute))
		return FALSE;

	request->cNumAttributes++;
	if(_wcsicmp(szAttribute, L"unicodePwd") == 0 ||
		_wcsicmp(szAttribute, L"currentValue") == 0 ||
		_wcsicmp(szAttribute, L"dBCSPwd") == 0 ||
		_wcsicmp(szAttribute, L"initialAuthIncoming") == 0 ||
		_wcsicmp(szAttribute, L"lmPwdHistory") == 0 ||
		_wcsicmp(szAttribute, L"ntPwdHistory") == 0 ||
		_wcsicmp(szAttribute, L"priorValue") == 0 ||
		_wcsicmp(szAttribute, L"supplementalCredentials") == 0 ||
		_wcsicmp(szAttribute, L"trustAuthIncoming") == 0 ||
		_wcsicmp(szAttribute, L"trustAuthOutgoing") == 0)
	{
		(*pProperty)->fIsSensitive = TRUE;
	}
	return TRUE;
}