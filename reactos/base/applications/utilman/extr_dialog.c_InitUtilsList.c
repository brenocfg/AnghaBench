#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* szResource; scalar_t__ bState; int /*<<< orphan*/  lpProgram; int /*<<< orphan*/  uNameId; } ;
typedef  TYPE_1__ WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t UINT ;
struct TYPE_9__ {int /*<<< orphan*/  hListDlg; int /*<<< orphan*/  szNotRunning; int /*<<< orphan*/  szRunning; int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 TYPE_1__* EntriesList ; 
 scalar_t__ FALSE ; 
 TYPE_6__ Globals ; 
 scalar_t__ IsProcessRunning (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_ADDSTRING ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int MAX_BUFFER ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringCchPrintfW (TYPE_1__*,size_t,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t _countof (TYPE_1__*) ; 

VOID InitUtilsList(BOOL bInitGui)
{
    UINT i;

    if (!bInitGui)
    {
        // TODO: Load the list dynamically from the registry key
        // hklm\software\microsoft\windows nt\currentversion\accessibility

        /* Initialize the resource utility strings only once */
        for (i = 0; i < _countof(EntriesList); ++i)
        {
            LoadStringW(Globals.hInstance, EntriesList[i].uNameId,
                        EntriesList[i].szResource, _countof(EntriesList[i].szResource));

            EntriesList[i].bState = FALSE;
        }
    }
    else
    {
        INT iItem;
        BOOL bIsRunning;
        WCHAR szFormat[MAX_BUFFER];

        /* Reset the listbox */
        SendMessageW(Globals.hListDlg, LB_RESETCONTENT, 0, 0);

        /* Add the utilities in the listbox */
        for (i = 0; i < _countof(EntriesList); ++i)
        {
            bIsRunning = IsProcessRunning(EntriesList[i].lpProgram);
            EntriesList[i].bState = bIsRunning;

            /* Load the string and append the utility's name to the format */
            StringCchPrintfW(szFormat, _countof(szFormat),
                             (bIsRunning ? Globals.szRunning : Globals.szNotRunning),
                             EntriesList[i].szResource);

            /* Add the item in the listbox */
            iItem = (INT)SendMessageW(Globals.hListDlg, LB_ADDSTRING, 0, (LPARAM)szFormat);
            if (iItem != LB_ERR)
                SendMessageW(Globals.hListDlg, LB_SETITEMDATA, iItem, (LPARAM)&EntriesList[i]);
        }
    }
}