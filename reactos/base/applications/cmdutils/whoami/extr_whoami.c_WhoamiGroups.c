#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmpBuffer ;
typedef  int /*<<< orphan*/  szGroupName ;
typedef  int /*<<< orphan*/  szDomainName ;
typedef  int /*<<< orphan*/  WhoamiTable ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_4__ {size_t GroupCount; TYPE_1__* Groups; } ;
struct TYPE_3__ {int Attributes; int /*<<< orphan*/  Sid; } ;
typedef  size_t SID_NAME_USE ;
typedef  TYPE_2__* PTOKEN_GROUPS ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  size_t DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidW (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int IDS_ATTR_GROUP_ENABLED ; 
 int IDS_ATTR_GROUP_ENABLED_BY_DEFAULT ; 
 int IDS_ATTR_GROUP_MANDATORY ; 
 int IDS_ATTR_GROUP_OWNER ; 
 int IDS_COL_ATTRIB ; 
 int IDS_COL_GROUP_NAME ; 
 int IDS_COL_SID ; 
 int IDS_COL_TYPE ; 
 int /*<<< orphan*/  IDS_GROU_HEADER ; 
 int IDS_TP_ALIAS ; 
 int IDS_TP_LABEL ; 
 int IDS_TP_WELL_KNOWN_GROUP ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LookupAccountSidW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int SE_GROUP_ENABLED ; 
 int SE_GROUP_ENABLED_BY_DEFAULT ; 
 int SE_GROUP_LOGON_ID ; 
 int SE_GROUP_MANDATORY ; 
 int SE_GROUP_OWNER ; 
 size_t SidTypeAlias ; 
 size_t SidTypeLabel ; 
 size_t SidTypeWellKnownGroup ; 
 int /*<<< orphan*/  StringCchCat (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TokenGroups ; 
 int /*<<< orphan*/  UNICODE_NULL ; 
 int /*<<< orphan*/ * WhoamiAllocTable (size_t,int) ; 
 int /*<<< orphan*/  WhoamiFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiGetTokenInfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WhoamiLoadRcString (int) ; 
 int /*<<< orphan*/  WhoamiPrintHeader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WhoamiPrintTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WhoamiSetTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 size_t _countof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _snwprintf (int /*<<< orphan*/ *,size_t,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 size_t max (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

int WhoamiGroups(void)
{
    DWORD dwIndex = 0;
    LPWSTR pSidStr = 0;

    static WCHAR szGroupName[255] = {0};
    static WCHAR szDomainName[255] = {0};

    DWORD cchGroupName  = _countof(szGroupName);
    DWORD cchDomainName = _countof(szGroupName);

    SID_NAME_USE Use = 0;
    BYTE SidNameUseStr[12] =
    {
        /* SidTypeUser           */ -1,
        /* SidTypeGroup          */ -1,
        /* SidTypeDomain         */ -1,
        /* SidTypeUser           */ -1,
        /* SidTypeAlias          */ IDS_TP_ALIAS,
        /* SidTypeWellKnownGroup */ IDS_TP_WELL_KNOWN_GROUP,
        /* SidTypeDeletedAccount */ -1,
        /* SidTypeInvalid        */ -1,
        /* SidTypeUnknown        */ -1,
        /* SidTypeComputer       */ -1,
        /* SidTypeLabel          */ IDS_TP_LABEL
    };

    PTOKEN_GROUPS pGroupInfo = (PTOKEN_GROUPS)WhoamiGetTokenInfo(TokenGroups);
    UINT PrintingRow;
    WhoamiTable *GroupTable = NULL;

    if (pGroupInfo == NULL)
    {
        return 1;
    }

    /* the header is the first (0) row, so we start in the second one (1) */
    PrintingRow = 1;

    GroupTable = WhoamiAllocTable(pGroupInfo->GroupCount + 1, 4);

    WhoamiPrintHeader(IDS_GROU_HEADER);

    WhoamiSetTable(GroupTable, WhoamiLoadRcString(IDS_COL_GROUP_NAME), 0, 0);
    WhoamiSetTable(GroupTable, WhoamiLoadRcString(IDS_COL_TYPE), 0, 1);
    WhoamiSetTable(GroupTable, WhoamiLoadRcString(IDS_COL_SID), 0, 2);
    WhoamiSetTable(GroupTable, WhoamiLoadRcString(IDS_COL_ATTRIB), 0, 3);

    for (dwIndex = 0; dwIndex < pGroupInfo->GroupCount; dwIndex++)
    {
        LookupAccountSidW(NULL,
                          pGroupInfo->Groups[dwIndex].Sid,
                          (LPWSTR)&szGroupName,
                          &cchGroupName,
                          (LPWSTR)&szDomainName,
                          &cchDomainName,
                          &Use);

        /* the original tool seems to limit the list to these kind of SID items */
        if ((Use == SidTypeWellKnownGroup || Use == SidTypeAlias ||
            Use == SidTypeLabel) && !(pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_LOGON_ID))
        {
                wchar_t tmpBuffer[666];

            /* looks like windows treats 0x60 as 0x7 for some reason, let's just nod and call it a day:
               0x60 is SE_GROUP_INTEGRITY | SE_GROUP_INTEGRITY_ENABLED
               0x07 is SE_GROUP_MANDATORY | SE_GROUP_ENABLED_BY_DEFAULT | SE_GROUP_ENABLED */

            if (pGroupInfo->Groups[dwIndex].Attributes == 0x60)
                pGroupInfo->Groups[dwIndex].Attributes = 0x07;

            /* 1- format it as DOMAIN\GROUP if the domain exists, or just GROUP if not */
            _snwprintf((LPWSTR)&tmpBuffer,
                       _countof(tmpBuffer),
                       L"%s%s%s",
                       szDomainName,
                       cchDomainName ? L"\\" : L"",
                       szGroupName);

            WhoamiSetTable(GroupTable, tmpBuffer, PrintingRow, 0);

            /* 2- let's find out the group type by using a simple lookup table for lack of a better method */
            WhoamiSetTable(GroupTable, WhoamiLoadRcString(SidNameUseStr[Use]), PrintingRow, 1);

            /* 3- turn that SID into text-form */
            ConvertSidToStringSidW(pGroupInfo->Groups[dwIndex].Sid, &pSidStr);

            WhoamiSetTable(GroupTable, pSidStr, PrintingRow, 2);

            LocalFree(pSidStr);

            /* 4- reuse that buffer for appending the attributes in text-form at the very end */
            ZeroMemory(tmpBuffer, sizeof(tmpBuffer));

            if (pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_MANDATORY)
                StringCchCat(tmpBuffer, _countof(tmpBuffer), WhoamiLoadRcString(IDS_ATTR_GROUP_MANDATORY));
            if (pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_ENABLED_BY_DEFAULT)
                StringCchCat(tmpBuffer, _countof(tmpBuffer), WhoamiLoadRcString(IDS_ATTR_GROUP_ENABLED_BY_DEFAULT));
            if (pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_ENABLED)
                StringCchCat(tmpBuffer, _countof(tmpBuffer), WhoamiLoadRcString(IDS_ATTR_GROUP_ENABLED));
            if (pGroupInfo->Groups[dwIndex].Attributes & SE_GROUP_OWNER)
                StringCchCat(tmpBuffer, _countof(tmpBuffer), WhoamiLoadRcString(IDS_ATTR_GROUP_OWNER));

            /* remove the last comma (', ' which is 2 wchars) of the buffer, let's keep it simple */
            tmpBuffer[max(wcslen(tmpBuffer) - 2, 0)] = UNICODE_NULL;

            WhoamiSetTable(GroupTable, tmpBuffer, PrintingRow, 3);

            PrintingRow++;
        }

        /* reset the buffers so that we can reuse them */
        ZeroMemory(szGroupName, sizeof(szGroupName));
        ZeroMemory(szDomainName, sizeof(szDomainName));

        cchGroupName = 255;
        cchDomainName = 255;
    }

    WhoamiPrintTable(GroupTable);

    /* cleanup our allocations */
    WhoamiFree((LPVOID)pGroupInfo);

    return 0;
}