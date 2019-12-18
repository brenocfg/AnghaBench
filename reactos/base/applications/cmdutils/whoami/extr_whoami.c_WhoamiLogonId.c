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
struct TYPE_5__ {size_t GroupCount; TYPE_1__* Groups; } ;
struct TYPE_4__ {int Attributes; scalar_t__ Sid; } ;
typedef  TYPE_2__* PTOKEN_GROUPS ;
typedef  scalar_t__ PSID ;
typedef  char* LPWSTR ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidW (scalar_t__,char**) ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int SE_GROUP_LOGON_ID ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  WhoamiFree (TYPE_2__*) ; 
 int /*<<< orphan*/  WhoamiGetTokenInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wprintf (char*,...) ; 

int WhoamiLogonId(void)
{
    PTOKEN_GROUPS pGroupInfo = (PTOKEN_GROUPS) WhoamiGetTokenInfo(TokenGroups);
    DWORD dwIndex = 0;
    LPWSTR pSidStr = 0;
    PSID pSid = 0;

    if (pGroupInfo == NULL)
        return 0;

    /* lets see if we can find the logon SID in that list, should be there */
    for (dwIndex = 0; dwIndex < pGroupInfo->GroupCount; dwIndex++)
    {
        if ((pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_LOGON_ID) == SE_GROUP_LOGON_ID)
        {
            pSid = pGroupInfo->Groups[dwIndex].Sid;
        }
    }

    if (pSid == 0)
    {
        WhoamiFree(pGroupInfo);
        wprintf(L"ERROR: Couldn't find the logon SID.\n");
        return 1;
    }
    if (!ConvertSidToStringSidW(pSid, &pSidStr))
    {
        WhoamiFree(pGroupInfo);
        wprintf(L"ERROR: Couldn't convert the logon SID to a string.\n");
        return 1;
    }
    else
    {
        /* let's show our converted logon SID */
        wprintf(L"%s\n", pSidStr);
    }

    /* cleanup our allocations */
    LocalFree(pSidStr);
    WhoamiFree(pGroupInfo);

    return 0;
}