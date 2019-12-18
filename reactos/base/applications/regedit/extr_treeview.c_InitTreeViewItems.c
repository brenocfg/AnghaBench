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
struct TYPE_4__ {int mask; int cChildren; scalar_t__ lParam; void* iSelectedImage; void* iImage; int /*<<< orphan*/  pszText; int /*<<< orphan*/  cchTextMax; } ;
struct TYPE_5__ {int /*<<< orphan*/  hParent; scalar_t__ hInsertAfter; TYPE_1__ item; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  TYPE_2__ TVINSERTSTRUCTW ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__ LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HTREEITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddEntryToTree (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetVersion () ; 
 int /*<<< orphan*/  HKEY_CLASSES_ROOT ; 
 int /*<<< orphan*/  HKEY_CURRENT_CONFIG ; 
 int /*<<< orphan*/  HKEY_CURRENT_USER ; 
 int /*<<< orphan*/  HKEY_DYN_DATA ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  HKEY_USERS ; 
 void* Image_Root ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TVE_EXPAND ; 
 int /*<<< orphan*/  TVGN_CARET ; 
 int TVIF_CHILDREN ; 
 int TVIF_IMAGE ; 
 int TVIF_PARAM ; 
 int TVIF_SELECTEDIMAGE ; 
 int TVIF_TEXT ; 
 scalar_t__ TVI_FIRST ; 
 int /*<<< orphan*/  TVI_ROOT ; 
 int /*<<< orphan*/  TreeView_Expand (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TreeView_InsertItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TreeView_Select (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL InitTreeViewItems(HWND hwndTV, LPWSTR pHostName)
{
    TVITEMW tvi;
    TVINSERTSTRUCTW tvins;
    HTREEITEM hRoot;

    tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN | TVIF_PARAM;
    /* Set the text of the item.  */
    tvi.pszText = pHostName;
    tvi.cchTextMax = wcslen(tvi.pszText);
    /* Assume the item is not a parent item, so give it an image.  */
    tvi.iImage = Image_Root;
    tvi.iSelectedImage = Image_Root;
    tvi.cChildren = 5;
    /* Save the heading level in the item's application-defined data area.  */
    tvi.lParam = (LPARAM)NULL;
    tvins.item = tvi;
    tvins.hInsertAfter = (HTREEITEM)TVI_FIRST;
    tvins.hParent = TVI_ROOT;
    /* Add the item to the tree view control.  */
    if (!(hRoot = TreeView_InsertItem(hwndTV, &tvins))) return FALSE;

    if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT, 1)) return FALSE;
    if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_CURRENT_USER", HKEY_CURRENT_USER, 1)) return FALSE;
    if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE, 1)) return FALSE;
    if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_USERS", HKEY_USERS, 1)) return FALSE;
    if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG, 1)) return FALSE;

    if (GetVersion() & 0x80000000)
    {
        /* Win9x specific key */
        if (!AddEntryToTree(hwndTV, hRoot, L"HKEY_DYN_DATA", HKEY_DYN_DATA, 1)) return FALSE;
    }

    /* expand and select host name */
    (void)TreeView_Expand(hwndTV, hRoot, TVE_EXPAND);
    (void)TreeView_Select(hwndTV, hRoot, TVGN_CARET);
    return TRUE;
}