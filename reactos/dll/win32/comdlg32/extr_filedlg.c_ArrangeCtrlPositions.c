#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int bottom; int right; scalar_t__ left; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 int /*<<< orphan*/  GetClientRect (scalar_t__,TYPE_1__*) ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int SWP_NOZORDER ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pshHelp ; 
 int /*<<< orphan*/  stc32 ; 
 int /*<<< orphan*/  wine_dbgstr_rect (TYPE_1__*) ; 

__attribute__((used)) static void ArrangeCtrlPositions(HWND hwndChildDlg, HWND hwndParentDlg, BOOL hide_help)
{
    HWND hwndChild, hwndStc32;
    RECT rectParent, rectChild, rectStc32;
    INT help_fixup = 0;
    int chgx, chgy;

    /* Take into account if open as read only checkbox and help button
     * are hidden
     */
     if (hide_help)
     {
         RECT rectHelp, rectCancel;
         GetWindowRect(GetDlgItem(hwndParentDlg, pshHelp), &rectHelp);
         GetWindowRect(GetDlgItem(hwndParentDlg, IDCANCEL), &rectCancel);
         /* subtract the height of the help button plus the space between
          * the help button and the cancel button to the height of the dialog
          */
          help_fixup = rectHelp.bottom - rectCancel.bottom;
    }

    /*
      There are two possibilities to add components to the default file dialog box.

      By default, all the new components are added below the standard dialog box (the else case).

      However, if there is a static text component with the stc32 id, a special case happens.
      The x and y coordinates of stc32 indicate the top left corner where to place the standard file dialog box
      in the window and the cx and cy indicate how to size the window.
      Moreover, if the new component's coordinates are on the left of the stc32 , it is placed on the left 
      of the standard file dialog box. If they are above the stc32 component, it is placed above and so on....
      
     */

    GetClientRect(hwndParentDlg, &rectParent);

    /* when arranging controls we have to use fixed parent size */
    rectParent.bottom -= help_fixup;

    hwndStc32 = GetDlgItem(hwndChildDlg, stc32);
    if (hwndStc32)
    {
        GetWindowRect(hwndStc32, &rectStc32);
        MapWindowPoints(0, hwndChildDlg, (LPPOINT)&rectStc32, 2);

        /* set the size of the stc32 control according to the size of
         * client area of the parent dialog
         */
        SetWindowPos(hwndStc32, 0,
                     0, 0,
                     rectParent.right, rectParent.bottom,
                     SWP_NOMOVE | SWP_NOZORDER);
    }
    else
        SetRectEmpty(&rectStc32);

    /* this part moves controls of the child dialog */
    hwndChild = GetWindow(hwndChildDlg, GW_CHILD);
    while (hwndChild)
    {
        if (hwndChild != hwndStc32)
        {
            GetWindowRect(hwndChild, &rectChild);
            MapWindowPoints(0, hwndChildDlg, (LPPOINT)&rectChild, 2);

            /* move only if stc32 exist */
            if (hwndStc32 && rectChild.left > rectStc32.right)
            {
                /* move to the right of visible controls of the parent dialog */
                rectChild.left += rectParent.right;
                rectChild.left -= rectStc32.right;
            }
            /* move even if stc32 doesn't exist */
            if (rectChild.top >= rectStc32.bottom)
            {
                /* move below visible controls of the parent dialog */
                rectChild.top += rectParent.bottom;
                rectChild.top -= rectStc32.bottom - rectStc32.top;
            }

            SetWindowPos(hwndChild, 0, rectChild.left, rectChild.top,
                         0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    }

    /* this part moves controls of the parent dialog */
    hwndChild = GetWindow(hwndParentDlg, GW_CHILD);
    while (hwndChild)
    {
        if (hwndChild != hwndChildDlg)
        {
            GetWindowRect(hwndChild, &rectChild);
            MapWindowPoints(0, hwndParentDlg, (LPPOINT)&rectChild, 2);

            /* left,top of stc32 marks the position of controls
             * from the parent dialog
             */
            rectChild.left += rectStc32.left;
            rectChild.top += rectStc32.top;

            SetWindowPos(hwndChild, 0, rectChild.left, rectChild.top,
                         0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        hwndChild = GetWindow(hwndChild, GW_HWNDNEXT);
    }

    /* calculate the size of the resulting dialog */

    /* here we have to use original parent size */
    GetClientRect(hwndParentDlg, &rectParent);
    GetClientRect(hwndChildDlg, &rectChild);
    TRACE( "parent %s child %s stc32 %s\n", wine_dbgstr_rect( &rectParent),
            wine_dbgstr_rect( &rectChild), wine_dbgstr_rect( &rectStc32));

    if (hwndStc32)
    {
        /* width */
        if (rectParent.right > rectStc32.right - rectStc32.left)
            chgx = rectChild.right - ( rectStc32.right - rectStc32.left);
        else
            chgx = rectChild.right - rectParent.right;
        /* height */
        if (rectParent.bottom > rectStc32.bottom - rectStc32.top)
            chgy = rectChild.bottom - ( rectStc32.bottom - rectStc32.top) - help_fixup;
        else
            /* Unconditionally set new dialog
             * height to that of the child
             */
            chgy = rectChild.bottom - rectParent.bottom;
    }
    else
    {
        chgx = 0;
        chgy = rectChild.bottom - help_fixup;
    }
    /* set the size of the parent dialog */
    GetWindowRect(hwndParentDlg, &rectParent);
    SetWindowPos(hwndParentDlg, 0,
                 0, 0,
                 rectParent.right - rectParent.left + chgx,
                 rectParent.bottom - rectParent.top + chgy,
                 SWP_NOMOVE | SWP_NOZORDER);
}