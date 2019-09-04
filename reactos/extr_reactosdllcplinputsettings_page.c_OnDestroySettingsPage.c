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
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/ * HIMAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_KEYLAYOUT_LIST ; 
 int /*<<< orphan*/  ImageList_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InputList_Destroy () ; 
 int /*<<< orphan*/  LVSIL_SMALL ; 
 int /*<<< orphan*/  LayoutList_Destroy () ; 
 int /*<<< orphan*/ * ListView_GetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocaleList_Destroy () ; 

__attribute__((used)) static VOID
OnDestroySettingsPage(HWND hwndDlg)
{
    HIMAGELIST hImageList;

    LayoutList_Destroy();
    LocaleList_Destroy();
    InputList_Destroy();

    hImageList = ListView_GetImageList(GetDlgItem(hwndDlg, IDC_KEYLAYOUT_LIST),
                                       LVSIL_SMALL);
    if (hImageList != NULL)
    {
        ImageList_Destroy(hImageList);
    }
}