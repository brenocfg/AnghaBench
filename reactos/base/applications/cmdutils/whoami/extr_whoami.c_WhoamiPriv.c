#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WhoamiTable ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {size_t PrivilegeCount; TYPE_1__* Privileges; } ;
struct TYPE_10__ {int Attributes; int /*<<< orphan*/  Luid; } ;
typedef  TYPE_2__* PWSTR ;
typedef  TYPE_2__* PTOKEN_PRIVILEGES ;
typedef  size_t DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  IDS_COL_DESCRIPTION ; 
 int /*<<< orphan*/  IDS_COL_PRIV_NAME ; 
 int /*<<< orphan*/  IDS_COL_STATE ; 
 int /*<<< orphan*/  IDS_PRIV_HEADER ; 
 int /*<<< orphan*/  IDS_STATE_DISABLED ; 
 int /*<<< orphan*/  IDS_STATE_ENABLED ; 
 int /*<<< orphan*/  IDS_UNKNOWN_DESCRIPTION ; 
 scalar_t__ LookupPrivilegeDisplayNameW (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,size_t*,size_t*) ; 
 scalar_t__ LookupPrivilegeNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,size_t*) ; 
 int SE_PRIVILEGE_ENABLED ; 
 int /*<<< orphan*/  TokenPrivileges ; 
 int /*<<< orphan*/ * WhoamiAllocTable (size_t,int) ; 
 int /*<<< orphan*/  WhoamiFree (TYPE_2__*) ; 
 int /*<<< orphan*/  WhoamiGetTokenInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiLoadRcString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiPrintHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiPrintTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WhoamiSetTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  WhoamiSetTableDyn (int /*<<< orphan*/ *,TYPE_2__*,size_t,int) ; 

int WhoamiPriv(void)
{
    PTOKEN_PRIVILEGES pPrivInfo = (PTOKEN_PRIVILEGES) WhoamiGetTokenInfo(TokenPrivileges);
    DWORD dwResult = 0, dwIndex = 0;
    WhoamiTable *PrivTable = NULL;

    if (pPrivInfo == NULL)
    {
        return 1;
    }

    PrivTable = WhoamiAllocTable(pPrivInfo->PrivilegeCount + 1, 3);

    WhoamiPrintHeader(IDS_PRIV_HEADER);

    WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_COL_PRIV_NAME), 0, 0);
    WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_COL_DESCRIPTION), 0, 1);
    WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_COL_STATE), 0, 2);

    for (dwIndex = 0; dwIndex < pPrivInfo->PrivilegeCount; dwIndex++)
    {
        PWSTR PrivName = NULL, DispName = NULL;
        DWORD PrivNameSize = 0, DispNameSize = 0;
        BOOL ret = FALSE;

        ret = LookupPrivilegeNameW(NULL,
                                   &pPrivInfo->Privileges[dwIndex].Luid,
                                   NULL,
                                   &PrivNameSize);

        PrivName = HeapAlloc(GetProcessHeap(), 0, ++PrivNameSize*sizeof(WCHAR));

        LookupPrivilegeNameW(NULL,
                             &pPrivInfo->Privileges[dwIndex].Luid,
                             PrivName,
                             &PrivNameSize);

        WhoamiSetTableDyn(PrivTable, PrivName, dwIndex + 1, 0);


        /* try to grab the size of the string, also, beware, as this call is
           unimplemented in ReactOS/Wine at the moment */

        LookupPrivilegeDisplayNameW(NULL, PrivName, NULL, &DispNameSize, &dwResult);

        DispName = HeapAlloc(GetProcessHeap(), 0, ++DispNameSize * sizeof(WCHAR));

        ret = LookupPrivilegeDisplayNameW(NULL, PrivName, DispName, &DispNameSize, &dwResult);

        if (ret && DispName)
        {
            // wprintf(L"DispName: %d %x '%s'\n", DispNameSize, GetLastError(), DispName);
            WhoamiSetTableDyn(PrivTable, DispName, dwIndex + 1, 1);
        }
        else
        {
            WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_UNKNOWN_DESCRIPTION), dwIndex + 1, 1);

            if (DispName != NULL)
                WhoamiFree(DispName);
        }

        if (pPrivInfo->Privileges[dwIndex].Attributes & SE_PRIVILEGE_ENABLED)
            WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_STATE_ENABLED),  dwIndex + 1, 2);
        else
            WhoamiSetTable(PrivTable, WhoamiLoadRcString(IDS_STATE_DISABLED), dwIndex + 1, 2);
    }

    WhoamiPrintTable(PrivTable);

    /* cleanup our allocations */
    WhoamiFree(pPrivInfo);

    return 0;
}