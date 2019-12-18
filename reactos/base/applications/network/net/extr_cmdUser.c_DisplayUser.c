#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int usri4_flags; scalar_t__ usri4_acct_expires; scalar_t__ usri4_password_age; scalar_t__ usrmod0_max_passwd_age; scalar_t__ usrmod0_min_passwd_age; scalar_t__ usri4_last_logon; int /*<<< orphan*/ * grui0_name; int /*<<< orphan*/ * lgrui0_name; int /*<<< orphan*/ * usri4_logon_hours; int /*<<< orphan*/  usri4_units_per_week; int /*<<< orphan*/ * usri4_home_dir; int /*<<< orphan*/ * usri4_profile; int /*<<< orphan*/ * usri4_script_path; int /*<<< orphan*/ * usri4_workstations; int /*<<< orphan*/  usri4_country_code; int /*<<< orphan*/ * usri4_usr_comment; int /*<<< orphan*/ * usri4_comment; int /*<<< orphan*/ * usri4_full_name; int /*<<< orphan*/ * usri4_name; } ;
typedef  TYPE_1__* PUSER_MODALS_INFO_0 ;
typedef  TYPE_1__* PUSER_INFO_4 ;
typedef  TYPE_1__* PLOCALGROUP_USERS_INFO_0 ;
typedef  TYPE_1__* PGROUP_USERS_INFO_0 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetCountryFromCountryCode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetTimeInSeconds () ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetUserGetGroups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ NetUserGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NetUserGetLocalGroups (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 scalar_t__ NetUserModalsGet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintDateTime (scalar_t__) ; 
 int /*<<< orphan*/  PrintLogonHours (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintPaddedMessageString (int,int) ; 
 int /*<<< orphan*/  PrintPadding (int,int) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TIMEQ_FOREVER ; 
 int UF_ACCOUNTDISABLE ; 
 int UF_DONT_EXPIRE_PASSWD ; 
 int UF_LOCKOUT ; 
 int UF_PASSWD_CANT_CHANGE ; 
 int UF_PASSWD_NOTREQD ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
NET_API_STATUS
DisplayUser(LPWSTR lpUserName)
{
    PUSER_MODALS_INFO_0 pUserModals = NULL;
    PUSER_INFO_4 pUserInfo = NULL;
    PLOCALGROUP_USERS_INFO_0 pLocalGroupInfo = NULL;
    PGROUP_USERS_INFO_0 pGroupInfo = NULL;
    DWORD dwLocalGroupRead, dwLocalGroupTotal;
    DWORD dwGroupRead, dwGroupTotal;
    DWORD dwLastSet;
    DWORD i;
    WCHAR szCountry[40];
    INT nPaddedLength = 36;
    NET_API_STATUS Status;

    /* Modify the user */
    Status = NetUserGetInfo(NULL,
                            lpUserName,
                            4,
                            (LPBYTE*)&pUserInfo);
    if (Status != NERR_Success)
        return Status;

    Status = NetUserModalsGet(NULL,
                              0,
                              (LPBYTE*)&pUserModals);
    if (Status != NERR_Success)
        goto done;

    Status = NetUserGetLocalGroups(NULL,
                                   lpUserName,
                                   0,
                                   0,
                                   (LPBYTE*)&pLocalGroupInfo,
                                   MAX_PREFERRED_LENGTH,
                                   &dwLocalGroupRead,
                                   &dwLocalGroupTotal);
    if (Status != NERR_Success)
        goto done;

    Status = NetUserGetGroups(NULL,
                              lpUserName,
                              0,
                              (LPBYTE*)&pGroupInfo,
                              MAX_PREFERRED_LENGTH,
                              &dwGroupRead,
                              &dwGroupTotal);
    if (Status != NERR_Success)
        goto done;

    PrintPaddedMessageString(4411, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_name);

    PrintPaddedMessageString(4412, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_full_name);

    PrintPaddedMessageString(4413, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_comment);

    PrintPaddedMessageString(4414, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_usr_comment);

    PrintPaddedMessageString(4416, nPaddedLength);
    GetCountryFromCountryCode(pUserInfo->usri4_country_code,
                              ARRAYSIZE(szCountry), szCountry);
    ConPrintf(StdOut, L"%03ld (%s)\n", pUserInfo->usri4_country_code, szCountry);

    PrintPaddedMessageString(4419, nPaddedLength);
    if (pUserInfo->usri4_flags & UF_ACCOUNTDISABLE)
        PrintMessageString(4301);
    else if (pUserInfo->usri4_flags & UF_LOCKOUT)
        PrintMessageString(4440);
    else
        PrintMessageString(4300);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4420, nPaddedLength);
    if (pUserInfo->usri4_acct_expires == TIMEQ_FOREVER)
        PrintMessageString(4305);
    else
        PrintDateTime(pUserInfo->usri4_acct_expires);
    ConPuts(StdOut, L"\n\n");

    PrintPaddedMessageString(4421, nPaddedLength);
    dwLastSet = GetTimeInSeconds() - pUserInfo->usri4_password_age;
    PrintDateTime(dwLastSet);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4422, nPaddedLength);
    if ((pUserInfo->usri4_flags & UF_DONT_EXPIRE_PASSWD) || pUserModals->usrmod0_max_passwd_age == TIMEQ_FOREVER)
        PrintMessageString(4305);
    else
        PrintDateTime(dwLastSet + pUserModals->usrmod0_max_passwd_age);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4423, nPaddedLength);
    PrintDateTime(dwLastSet + pUserModals->usrmod0_min_passwd_age);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4437, nPaddedLength);
    PrintMessageString((pUserInfo->usri4_flags & UF_PASSWD_NOTREQD) ? 4301 : 4300);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4438, nPaddedLength);
    PrintMessageString((pUserInfo->usri4_flags & UF_PASSWD_CANT_CHANGE) ? 4301 : 4300);
    ConPuts(StdOut, L"\n\n");

    PrintPaddedMessageString(4424, nPaddedLength);
    if (pUserInfo->usri4_workstations == NULL || wcslen(pUserInfo->usri4_workstations) == 0)
        PrintMessageString(4302);
    else
        ConPrintf(StdOut, L"%s", pUserInfo->usri4_workstations);
    ConPuts(StdOut, L"\n");

    PrintPaddedMessageString(4429, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_script_path);

    PrintPaddedMessageString(4439, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_profile);

    PrintPaddedMessageString(4436, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pUserInfo->usri4_home_dir);

    PrintPaddedMessageString(4430, nPaddedLength);
    if (pUserInfo->usri4_last_logon == 0)
        PrintMessageString(4305);
    else
        PrintDateTime(pUserInfo->usri4_last_logon);
    ConPuts(StdOut, L"\n\n");

    PrintPaddedMessageString(4432, nPaddedLength);
    if (pUserInfo->usri4_logon_hours == NULL)
    {
        PrintMessageString(4302);
        ConPuts(StdOut, L"\n");
    }
    else
    {
        PrintLogonHours(pUserInfo->usri4_units_per_week,
                        pUserInfo->usri4_logon_hours,
                        nPaddedLength);
    }

    ConPuts(StdOut, L"\n");
    PrintPaddedMessageString(4427, nPaddedLength);
    if (dwLocalGroupTotal != 0 && pLocalGroupInfo != NULL)
    {
        for (i = 0; i < dwLocalGroupTotal; i++)
        {
            if (i != 0)
                PrintPadding(L' ', nPaddedLength);
            ConPrintf(StdOut, L"*%s\n", pLocalGroupInfo[i].lgrui0_name);
        }
    }
    else
    {
        ConPuts(StdOut, L"\n");
    }

    PrintPaddedMessageString(4431, nPaddedLength);
    if (dwGroupTotal != 0 && pGroupInfo != NULL)
    {
        for (i = 0; i < dwGroupTotal; i++)
        {
            if (i != 0)
                PrintPadding(L' ', nPaddedLength);
            ConPrintf(StdOut, L"*%s\n", pGroupInfo[i].grui0_name);
        }
    }
    else
    {
        ConPuts(StdOut, L"\n");
    }

done:
    if (pGroupInfo != NULL)
        NetApiBufferFree(pGroupInfo);

    if (pLocalGroupInfo != NULL)
        NetApiBufferFree(pLocalGroupInfo);

    if (pUserModals != NULL)
        NetApiBufferFree(pUserModals);

    if (pUserInfo != NULL)
        NetApiBufferFree(pUserInfo);

    return NERR_Success;
}