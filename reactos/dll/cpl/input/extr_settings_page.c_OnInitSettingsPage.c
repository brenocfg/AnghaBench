#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  column ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int mask; int iSubItem; int cx; int /*<<< orphan*/ * pszText; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ LV_COLUMN ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_KEYLAYOUT_LIST ; 
 int /*<<< orphan*/  IDS_LANGUAGE ; 
 int /*<<< orphan*/  IDS_LAYOUT ; 
 int ILC_COLOR8 ; 
 int ILC_MASK ; 
 int /*<<< orphan*/ * ImageList_Create (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InputList_Create () ; 
 int /*<<< orphan*/  LVCFMT_LEFT ; 
 int /*<<< orphan*/  LVCFMT_RIGHT ; 
 int LVCF_FMT ; 
 int LVCF_SUBITEM ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  LVS_EX_FULLROWSELECT ; 
 int /*<<< orphan*/  LayoutList_Create () ; 
 int /*<<< orphan*/  ListView_InsertColumn (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ListView_SetExtendedListViewStyle (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ListView_SetImageList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocaleList_Create () ; 
 int MAX_STR_LEN ; 
 int /*<<< orphan*/  SM_CXSMICON ; 
 int /*<<< orphan*/  SM_CYSMICON ; 
 int /*<<< orphan*/  SetControlsState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateInputListView (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hApplet ; 

__attribute__((used)) static VOID
OnInitSettingsPage(HWND hwndDlg)
{
    HWND hwndInputList;

    LayoutList_Create();
    LocaleList_Create();
    InputList_Create();

    hwndInputList = GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST);

    if (hwndInputList != NULL)
    {
        WCHAR szBuffer[MAX_STR_LEN];
        HIMAGELIST hLayoutImageList;
        LV_COLUMN column;

        ListView_SetExtendedListViewStyle(hwndInputList, LVS_EX_FULLROWSELECT);

        ZeroMemory(&column, sizeof(column));

        column.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

        LoadStringW(hApplet, IDS_LANGUAGE, szBuffer, ARRAYSIZE(szBuffer));
        column.fmt      = LVCFMT_LEFT;
        column.iSubItem = 0;
        column.pszText  = szBuffer;
        column.cx       = 175;
        ListView_InsertColumn(hwndInputList, 0, &column);

        LoadStringW(hApplet, IDS_LAYOUT, szBuffer, ARRAYSIZE(szBuffer));
        column.fmt      = LVCFMT_RIGHT;
        column.cx       = 155;
        column.iSubItem = 1;
        column.pszText  = szBuffer;
        ListView_InsertColumn(hwndInputList, 1, &column);

        hLayoutImageList = ImageList_Create(GetSystemMetrics(SM_CXSMICON) * 2,
                                            GetSystemMetrics(SM_CYSMICON),
                                            ILC_COLOR8 | ILC_MASK, 0, 0);
        if (hLayoutImageList != NULL)
        {
            HIMAGELIST hOldImagelist = ListView_SetImageList(hwndInputList, hLayoutImageList, LVSIL_SMALL);
            ImageList_Destroy(hOldImagelist);
        }

        UpdateInputListView(hwndInputList);
    }

    SetControlsState(hwndDlg, FALSE);
}