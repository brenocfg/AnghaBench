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
struct TYPE_5__ {int /*<<< orphan*/ * lgrmi3_domainandname; } ;
struct TYPE_4__ {int /*<<< orphan*/  szGroupName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  TYPE_1__* PGENERAL_GROUP_DATA ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_2__ LOCALGROUP_MEMBERS_INFO_3 ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DebugPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_MEMBER_IN_ALIAS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_USER_ADD_MEMBERSHIP_LIST ; 
 int /*<<< orphan*/  LVNI_SELECTED ; 
 int /*<<< orphan*/  ListView_GetItemText (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ListView_GetNextItem (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ListView_GetSelectedCount (int /*<<< orphan*/ ) ; 
 int MB_ICONERROR ; 
 int MB_OK ; 
 int /*<<< orphan*/  MessageBox (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NetLocalGroupAddMembers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int UNLEN ; 
 int /*<<< orphan*/  _TEXT (char*) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static BOOL
AddSelectedUsersToGroup(HWND hwndDlg,
                        PGENERAL_GROUP_DATA pGroupData)
{
    HWND hwndLV;
    INT nSelectedItems;
    INT nItem;
    TCHAR szUserName[UNLEN];
    BOOL bResult = FALSE;
    LOCALGROUP_MEMBERS_INFO_3 memberInfo;
    NET_API_STATUS status;

    hwndLV = GetDlgItem(hwndDlg, IDC_USER_ADD_MEMBERSHIP_LIST);

    nSelectedItems = ListView_GetSelectedCount(hwndLV);
    if (nSelectedItems > 0)
    {
        nItem = ListView_GetNextItem(hwndLV, -1, LVNI_SELECTED);
        while (nItem != -1)
        {
            /* Get the new user name */
            ListView_GetItemText(hwndLV,
                                 nItem, 0,
                                 szUserName,
                                 UNLEN);

            DebugPrintf(_TEXT("Selected user: %s"), szUserName);

            memberInfo.lgrmi3_domainandname = szUserName;

            status = NetLocalGroupAddMembers(NULL, pGroupData->szGroupName, 3,
                                             (LPBYTE)&memberInfo, 1);
            if (status != NERR_Success && status != ERROR_MEMBER_IN_ALIAS)
            {
                TCHAR szText[256];
                wsprintf(szText, TEXT("Error: %u"), status);
                MessageBox(NULL, szText, TEXT("NetLocalGroupAddMembers"), MB_ICONERROR | MB_OK);
            }
            else
            {
                bResult = TRUE;
            }

            nItem = ListView_GetNextItem(hwndLV, nItem, LVNI_SELECTED);
        }
    }

    return bResult;
}