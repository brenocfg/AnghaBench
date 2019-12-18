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
struct TYPE_10__ {int /*<<< orphan*/  Sid; } ;
struct TYPE_11__ {TYPE_1__ User; } ;
typedef  TYPE_2__* PTOKEN_USER ;
typedef  TYPE_2__* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidW (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  IDS_COL_SID ; 
 int /*<<< orphan*/  IDS_COL_USER_NAME ; 
 int /*<<< orphan*/  IDS_USER_HEADER ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  NameSamCompatible ; 
 int /*<<< orphan*/  TokenUser ; 
 int /*<<< orphan*/ * WhoamiAllocTable (int,int) ; 
 int /*<<< orphan*/  WhoamiFree (TYPE_2__*) ; 
 int /*<<< orphan*/  WhoamiGetTokenInfo (int /*<<< orphan*/ ) ; 
 TYPE_2__* WhoamiGetUser (int /*<<< orphan*/ ) ; 
 TYPE_2__* WhoamiLoadRcString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiPrintHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiPrintTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WhoamiSetTable (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 

int WhoamiUser(void)
{
    PTOKEN_USER pUserInfo = (PTOKEN_USER) WhoamiGetTokenInfo(TokenUser);
    LPWSTR pUserStr = NULL;
    LPWSTR pSidStr = NULL;
    WhoamiTable *UserTable = NULL;

    if (pUserInfo == NULL)
    {
        return 1;
    }

    pUserStr = WhoamiGetUser(NameSamCompatible);
    if (pUserStr == NULL)
    {
        WhoamiFree(pUserInfo);
        return 1;
    }

    UserTable = WhoamiAllocTable(2, 2);

    WhoamiPrintHeader(IDS_USER_HEADER);

    /* set the column labels */
    WhoamiSetTable(UserTable, WhoamiLoadRcString(IDS_COL_USER_NAME), 0, 0);
    WhoamiSetTable(UserTable, WhoamiLoadRcString(IDS_COL_SID), 0, 1);

    ConvertSidToStringSidW(pUserInfo->User.Sid, &pSidStr);

    /* set the values for our single row of data */
    WhoamiSetTable(UserTable, pUserStr, 1, 0);
    WhoamiSetTable(UserTable, pSidStr, 1, 1);

    WhoamiPrintTable(UserTable);

    /* cleanup our allocations */
    LocalFree(pSidStr);
    WhoamiFree(pUserInfo);
    WhoamiFree(pUserStr);

    return 0;
}