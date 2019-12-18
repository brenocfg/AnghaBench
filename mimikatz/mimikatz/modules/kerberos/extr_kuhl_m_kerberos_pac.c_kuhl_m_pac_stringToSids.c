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
struct TYPE_3__ {int /*<<< orphan*/  Attributes; int /*<<< orphan*/  Sid; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_1__* PKERB_SID_AND_ATTRIBUTES ;
typedef  scalar_t__ PCWSTR ;
typedef  int /*<<< orphan*/  KERB_SID_AND_ATTRIBUTES ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ConvertStringSidToSid (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DEFAULT_GROUP_ATTRIBUTES ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _wcsdup (scalar_t__) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wcstok_s (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 

BOOL kuhl_m_pac_stringToSids(PCWSTR szSids, PKERB_SID_AND_ATTRIBUTES *sids, DWORD *cbSids)
{
	PWSTR dupSids, nextSetToken, SetToken;
	DWORD i;
	PSID tmp = NULL;
	*sids = NULL;
	*cbSids = 0;
	if(szSids)
	{
		if(dupSids = _wcsdup(szSids))
		{
			for(nextSetToken = NULL, SetToken = wcstok_s(dupSids, L",", &nextSetToken); SetToken; SetToken = wcstok_s(NULL, L",", &nextSetToken))
			{
				if(ConvertStringSidToSid(SetToken, &tmp))
				{
					(*cbSids)++;
					LocalFree(tmp);
				}
			}
			free(dupSids);
		}
		if(*cbSids && (*sids = (PKERB_SID_AND_ATTRIBUTES) LocalAlloc(LPTR, *cbSids * sizeof(KERB_SID_AND_ATTRIBUTES))))
		{
			if(dupSids = _wcsdup(szSids))
			{
				for(i = 0, nextSetToken = NULL, SetToken = wcstok_s(dupSids, L",", &nextSetToken); (i < *cbSids) && SetToken; SetToken = wcstok_s(NULL, L",", &nextSetToken))
					if(ConvertStringSidToSid(SetToken, (PSID *) &(*sids)[i].Sid))
						(*sids)[i++].Attributes = DEFAULT_GROUP_ATTRIBUTES;
				free(dupSids);
			}
		}
	}
	return (*sids && *cbSids);
}