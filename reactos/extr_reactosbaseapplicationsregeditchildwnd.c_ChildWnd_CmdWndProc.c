#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int nFocusPanel; int /*<<< orphan*/  hTreeWnd; int /*<<< orphan*/  hListWnd; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HTREEITEM ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CopyKeyName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateNewKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExportRegistryFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FindDialog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetItemPath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  ID_EDIT_COPYKEYNAME 141 
#define  ID_EDIT_FIND 140 
#define  ID_EDIT_NEW_BINARYVALUE 139 
#define  ID_EDIT_NEW_DWORDVALUE 138 
#define  ID_EDIT_NEW_KEY 137 
#define  ID_EDIT_NEW_STRINGVALUE 136 
#define  ID_REGISTRY_EXIT 135 
#define  ID_SWITCH_PANELS 134 
#define  ID_TREE_COLLAPSEBRANCH 133 
#define  ID_TREE_DELETE 132 
#define  ID_TREE_EXPANDBRANCH 131 
#define  ID_TREE_EXPORT 130 
#define  ID_TREE_RENAME 129 
 int ID_TREE_SUGGESTION_MAX ; 
 int ID_TREE_SUGGESTION_MIN ; 
#define  ID_VIEW_REFRESH 128 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MB_ICONHAND ; 
 int /*<<< orphan*/  MessageBeep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Suggestions ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVE_COLLAPSE ; 
 int /*<<< orphan*/  TVE_EXPAND ; 
 int /*<<< orphan*/  TreeView_EditLabel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_Expand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TreeView_GetSelection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_COMMAND ; 
 TYPE_1__* g_pChildWnd ; 
 int /*<<< orphan*/  hFrameWnd ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ChildWnd_CmdWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HTREEITEM hSelection;
    HKEY hRootKey;
    LPCWSTR keyPath, s;
    WORD wID = LOWORD(wParam);

    UNREFERENCED_PARAMETER(message);

    switch (wID)
    {
        /* Parse the menu selections: */
    case ID_REGISTRY_EXIT:
        DestroyWindow(hWnd);
        break;
    case ID_VIEW_REFRESH:
        /* TODO */
        break;
    case ID_TREE_EXPANDBRANCH:
        TreeView_Expand(g_pChildWnd->hTreeWnd, TreeView_GetSelection(g_pChildWnd->hTreeWnd), TVE_EXPAND);
        break;
    case ID_TREE_COLLAPSEBRANCH:
        TreeView_Expand(g_pChildWnd->hTreeWnd, TreeView_GetSelection(g_pChildWnd->hTreeWnd), TVE_COLLAPSE);
        break;
    case ID_TREE_RENAME:
        SetFocus(g_pChildWnd->hTreeWnd);
        TreeView_EditLabel(g_pChildWnd->hTreeWnd, TreeView_GetSelection(g_pChildWnd->hTreeWnd));
        break;
    case ID_TREE_DELETE:
        hSelection = TreeView_GetSelection(g_pChildWnd->hTreeWnd);
        keyPath = GetItemPath(g_pChildWnd->hTreeWnd, hSelection, &hRootKey);

        if (keyPath == 0 || *keyPath == 0)
        {
            MessageBeep(MB_ICONHAND);
        }
        else if (DeleteKey(hWnd, hRootKey, keyPath))
            DeleteNode(g_pChildWnd->hTreeWnd, 0);
        break;
    case ID_TREE_EXPORT:
        ExportRegistryFile(g_pChildWnd->hTreeWnd);
        break;
    case ID_EDIT_FIND:
        FindDialog(hWnd);
        break;
    case ID_EDIT_COPYKEYNAME:
        hSelection = TreeView_GetSelection(g_pChildWnd->hTreeWnd);
        keyPath = GetItemPath(g_pChildWnd->hTreeWnd, hSelection, &hRootKey);
        CopyKeyName(hWnd, hRootKey, keyPath);
        break;
    case ID_EDIT_NEW_KEY:
        CreateNewKey(g_pChildWnd->hTreeWnd, TreeView_GetSelection(g_pChildWnd->hTreeWnd));
        break;
    case ID_EDIT_NEW_STRINGVALUE:
    case ID_EDIT_NEW_BINARYVALUE:
    case ID_EDIT_NEW_DWORDVALUE:
        SendMessageW(hFrameWnd, WM_COMMAND, wParam, lParam);
        break;
    case ID_SWITCH_PANELS:
        g_pChildWnd->nFocusPanel = !g_pChildWnd->nFocusPanel;
        SetFocus(g_pChildWnd->nFocusPanel? g_pChildWnd->hListWnd: g_pChildWnd->hTreeWnd);
        break;
    default:
        if ((wID >= ID_TREE_SUGGESTION_MIN) && (wID <= ID_TREE_SUGGESTION_MAX))
        {
            s = Suggestions;
            while(wID > ID_TREE_SUGGESTION_MIN)
            {
                if (*s)
                    s += wcslen(s) + 1;
                wID--;
            }
            SelectNode(g_pChildWnd->hTreeWnd, s);
            break;
        }
        return FALSE;
    }
    return TRUE;
}