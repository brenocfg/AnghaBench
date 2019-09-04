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
typedef  int LONG_PTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetComCtl32Version (int*,int*,int*) ; 
 int GetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDB_2K3CHECK ; 
 int /*<<< orphan*/  IDB_V7CHECK ; 
 int /*<<< orphan*/  ImageList_LoadBitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetWindowLongPtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TVSIL_STATE ; 
 int TVS_CHECKBOXES ; 
 int TVS_EX_PARTIALCHECKBOXES ; 
 int TreeView_GetExtendedStyle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_SetExtendedStyle (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_SetImageList (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInst ; 

void TreeView_Set3StateCheck(HWND hTree)
{
    LONG_PTR lStyle;
    DWORD dwExStyle;

    DWORD Major, Minor, Build;
    GetComCtl32Version(&Major, &Minor, &Build);

    /*
     * Choose the best way to handle 3-state TreeView checkboxes
     * according to the version of comctl32.dll we are running against.
     *
     * Starting version comctl32 version 6.10 (Vista+, via SxS)
     * we have native 3-state checkboxes available.
     * Only when comctl32 version 5.82 (no SxS) is available,
     * use its build number to know whether we should use 2k3-style
     * or Vista+ style check-boxes.
     */
    if (Major > 6 || (Major == 6 && Minor >= 10))
    {
        /*
         * NOTE: As explained in the following link:
         * http://stackoverflow.com/questions/31488233/treeview-setextendedstyle-does-not-apply-certain-styles-what-am-i-doing-wrong
         * the TreeView control should have the extended check-box style set
         * *BEFORE* actually setting the check-box window style, because it is
         * only at that step that the TreeView control builds its image list
         * containing the three check-box states. Indeed, if the extended
         * check-box style was applied after setting the window style, then
         * the image list would be already built with the default two states
         * and would not be updated.
         *
         * The MSDN documentation is not very clear on that point.
         *
         * Let me also take this opportunity to document what those
         * extended check-box state styles look like on Windows Vista+ :
         *
         * - TVS_EX_DIMMEDCHECKBOXES creates a grey tone version of the normal checked box state.
         * - TVS_EX_EXCLUSIONCHECKBOXES creates a red 'X'-style cross check-box state.
         * - TVS_EX_PARTIALCHECKBOXES creates a filled box.
         */
        dwExStyle = TreeView_GetExtendedStyle(hTree);
        TreeView_SetExtendedStyle(hTree, dwExStyle | TVS_EX_PARTIALCHECKBOXES, 0);

        lStyle = GetWindowLongPtr(hTree, GWL_STYLE);
        SetWindowLongPtr(hTree, GWL_STYLE, lStyle | TVS_CHECKBOXES);
    }
    else
    {
        lStyle = GetWindowLongPtr(hTree, GWL_STYLE);
        SetWindowLongPtr(hTree, GWL_STYLE, lStyle | TVS_CHECKBOXES);

        // TODO: Implement this function which should build at runtime
        // the image list with either two or three check-box states
        // (as it is done by the real common control TreeView), instead
        // of storing resource bitmaps.
        //
        // hCheckImageList = CreateCheckBoxImagelist(NULL, TRUE, TRUE, FALSE);
        TreeView_SetImageList(hTree,
                              ImageList_LoadBitmap(hInst, (Build >= 6000 ? MAKEINTRESOURCEW(IDB_V7CHECK) : MAKEINTRESOURCEW(IDB_2K3CHECK)), 16, 4, RGB(255, 255, 255)),
                              TVSIL_STATE);
    }
}