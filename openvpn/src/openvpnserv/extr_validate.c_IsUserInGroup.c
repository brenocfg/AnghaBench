#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_8__ {int /*<<< orphan*/  lgrmi0_sid; } ;
struct TYPE_7__ {size_t GroupCount; TYPE_1__* Groups; } ;
struct TYPE_6__ {int /*<<< orphan*/  Sid; } ;
typedef  TYPE_2__* PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_3__ LOCALGROUP_MEMBERS_INFO_0 ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 size_t ERROR_MORE_DATA ; 
 scalar_t__ EqualSid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ LookupSID (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  MsgToEventLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 size_t NERR_GroupNotFound ; 
 size_t NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_3__*) ; 
 size_t NetLocalGroupGetMembers (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,size_t*,int /*<<< orphan*/ *) ; 
 int SECURITY_MAX_SID_SIZE ; 
 int /*<<< orphan*/  SetLastError (size_t) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _countof (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL
IsUserInGroup(PSID sid, const PTOKEN_GROUPS token_groups, const WCHAR *group_name)
{
    BOOL ret = FALSE;
    DWORD_PTR resume = 0;
    DWORD err;
    BYTE grp_sid[SECURITY_MAX_SID_SIZE];
    int nloop = 0; /* a counter used to not get stuck in the do .. while() */

    /* first check in the token groups */
    if (token_groups && LookupSID(group_name, (PSID) grp_sid, _countof(grp_sid)))
    {
        for (DWORD i = 0; i < token_groups->GroupCount; ++i)
        {
            if (EqualSid((PSID) grp_sid, token_groups->Groups[i].Sid))
            {
                return TRUE;
            }
        }
    }

    /* check user's SID is a member of the group */
    if (!sid)
    {
        return FALSE;
    }
    do
    {
        DWORD nread, nmax;
        LOCALGROUP_MEMBERS_INFO_0 *members = NULL;
        err = NetLocalGroupGetMembers(NULL, group_name, 0, (LPBYTE *) &members,
                                      MAX_PREFERRED_LENGTH, &nread, &nmax, &resume);
        if ((err != NERR_Success && err != ERROR_MORE_DATA))
        {
            break;
        }
        /* If a match is already found, ret == TRUE and the loop is skipped */
        for (DWORD i = 0; i < nread && !ret; ++i)
        {
            ret = EqualSid(members[i].lgrmi0_sid, sid);
        }
        NetApiBufferFree(members);
        /* MSDN says the lookup should always iterate until err != ERROR_MORE_DATA */
    } while (err == ERROR_MORE_DATA && nloop++ < 100);

    if (err != NERR_Success && err != NERR_GroupNotFound)
    {
        SetLastError(err);
        MsgToEventLog(M_SYSERR, TEXT("In NetLocalGroupGetMembers for group '%s'"), group_name);
    }

    return ret;
}