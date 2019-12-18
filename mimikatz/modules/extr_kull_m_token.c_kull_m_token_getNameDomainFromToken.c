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
struct TYPE_5__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_6__ {TYPE_1__ User; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_2__* PTOKEN_USER ;
typedef  int /*<<< orphan*/  PSID_NAME_USE ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetTokenInformation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/  kull_m_token_getNameDomainFromSID (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOL kull_m_token_getNameDomainFromToken(HANDLE hToken, PWSTR * pName, PWSTR * pDomain, PWSTR * pSid, PSID_NAME_USE pSidNameUse)
{
	BOOL result = FALSE;
	PTOKEN_USER pTokenUser;
	DWORD szNeeded;

	if(!GetTokenInformation(hToken, TokenUser, NULL, 0, &szNeeded) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
	{
		if(pTokenUser = (PTOKEN_USER) LocalAlloc(LPTR, szNeeded))
		{
			if(GetTokenInformation(hToken, TokenUser, pTokenUser, szNeeded, &szNeeded))
			{
				if((result = kull_m_token_getNameDomainFromSID(pTokenUser->User.Sid, pName, pDomain, pSidNameUse, NULL)) && pSid)
					result = ConvertSidToStringSid(pTokenUser->User.Sid, pSid);
			}
			LocalFree(pTokenUser);
		}
	}
	return result;
}