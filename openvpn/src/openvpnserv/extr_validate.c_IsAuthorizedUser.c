#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/  PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetBuiltinAdminGroupName (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTokenGroups (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  IsUserInGroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  LookupAccountSidW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int MAX_NAME ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 char* SYSTEM_ADMIN_GROUP ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  _countof (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

BOOL
IsAuthorizedUser(PSID sid, const HANDLE token, const WCHAR *ovpn_admin_group)
{
    const WCHAR *admin_group[2];
    WCHAR username[MAX_NAME];
    WCHAR domain[MAX_NAME];
    WCHAR sysadmin_group[MAX_NAME];
    DWORD len = MAX_NAME;
    BOOL ret = FALSE;
    SID_NAME_USE sid_type;

    /* Get username */
    if (!LookupAccountSidW(NULL, sid, username, &len, domain, &len, &sid_type))
    {
        MsgToEventLog(M_SYSERR, TEXT("LookupAccountSid"));
        /* not fatal as this is now used only for logging */
        username[0] = '\0';
        domain[0] = '\0';
    }

    if (GetBuiltinAdminGroupName(sysadmin_group, _countof(sysadmin_group)))
    {
        admin_group[0] = sysadmin_group;
    }
    else
    {
        MsgToEventLog(M_SYSERR, TEXT("Failed to get the name of Administrators group. Using the default."));
        /* use the default value */
        admin_group[0] = SYSTEM_ADMIN_GROUP;
    }
    admin_group[1] = ovpn_admin_group;

    PTOKEN_GROUPS token_groups = GetTokenGroups(token);
    for (int i = 0; i < 2; ++i)
    {
        ret = IsUserInGroup(sid, token_groups, admin_group[i]);
        if (ret)
        {
            MsgToEventLog(M_INFO, TEXT("Authorizing user '%s@%s' by virtue of membership in group '%s'"),
                          username, domain, admin_group[i]);
            goto out;
        }
    }

out:
    free(token_groups);
    return ret;
}