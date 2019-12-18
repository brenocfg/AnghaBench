#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hwndTreeView; int /*<<< orphan*/  hWnd; TYPE_1__* lpBrowseInfo; } ;
typedef  TYPE_2__ browse_info ;
struct TYPE_6__ {int /*<<< orphan*/  ulFlags; int /*<<< orphan*/  pidlRoot; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IEnumIDList ;
typedef  scalar_t__ HTREEITEM ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HIMAGELIST ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  BrowseFlagsToSHCONTF (int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  ILClone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFindLastID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILRemoveLastID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellFolder_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ InsertTreeViewItem (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Shell_GetImageLists (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TVE_EXPAND ; 
 scalar_t__ TVI_ROOT ; 
 int /*<<< orphan*/  TVM_DELETEITEM ; 
 int /*<<< orphan*/  TVM_EXPAND ; 
 int /*<<< orphan*/  TVM_SETIMAGELIST ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ _ILIsDesktop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ILIsEmpty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void InitializeTreeView( browse_info *info )
{
    LPITEMIDLIST pidlParent, pidlChild;
    HIMAGELIST hImageList;
    HRESULT hr;
    IShellFolder *lpsfParent, *lpsfRoot;
    IEnumIDList * pEnumChildren = NULL;
    HTREEITEM item;
    DWORD flags;
    LPCITEMIDLIST root = info->lpBrowseInfo->pidlRoot;

    TRACE("%p\n", info );
    
    Shell_GetImageLists(NULL, &hImageList);

    if (hImageList)
        SendMessageW( info->hwndTreeView, TVM_SETIMAGELIST, 0, (LPARAM)hImageList );

    /* We want to call InsertTreeViewItem down the code, in order to insert
     * the root item of the treeview. Due to InsertTreeViewItem's signature, 
     * we need the following to do this:
     *
     * + An ITEMIDLIST corresponding to _the parent_ of root. 
     * + An ITEMIDLIST, which is a relative path from root's parent to root 
     *   (containing a single SHITEMID).
     * + An IShellFolder interface pointer of root's parent folder.
     *
     * If root is 'Desktop', then root's parent is also 'Desktop'.
     */

    pidlParent = ILClone(root);
    ILRemoveLastID(pidlParent);
    pidlChild = ILClone(ILFindLastID(root));
    
    if (_ILIsDesktop(pidlParent)) {
        hr = SHGetDesktopFolder(&lpsfParent);
    } else {
        IShellFolder *lpsfDesktop;
        hr = SHGetDesktopFolder(&lpsfDesktop);
        if (FAILED(hr)) {
            WARN("SHGetDesktopFolder failed! hr = %08x\n", hr);
            ILFree(pidlChild);
            ILFree(pidlParent);
            return;
        }
        hr = IShellFolder_BindToObject(lpsfDesktop, pidlParent, 0, &IID_IShellFolder, (LPVOID*)&lpsfParent);
        IShellFolder_Release(lpsfDesktop);
    }

    if (FAILED(hr)) {
        WARN("Could not bind to parent shell folder! hr = %08x\n", hr);
        ILFree(pidlChild);
        ILFree(pidlParent);
        return;
    }

    if (!_ILIsEmpty(pidlChild)) {
        hr = IShellFolder_BindToObject(lpsfParent, pidlChild, 0, &IID_IShellFolder, (LPVOID*)&lpsfRoot);
    } else {
        lpsfRoot = lpsfParent;
        hr = IShellFolder_AddRef(lpsfParent);
    }

    if (FAILED(hr)) {
        WARN("Could not bind to root shell folder! hr = %08x\n", hr);
        IShellFolder_Release(lpsfParent);
        ILFree(pidlChild);
        ILFree(pidlParent);
        return;
    }

    flags = BrowseFlagsToSHCONTF( info->lpBrowseInfo->ulFlags );
    hr = IShellFolder_EnumObjects( lpsfRoot, info->hWnd, flags, &pEnumChildren );
    if (FAILED(hr)) {
        WARN("Could not get child iterator! hr = %08x\n", hr);
        IShellFolder_Release(lpsfParent);
        IShellFolder_Release(lpsfRoot);
        ILFree(pidlChild);
        ILFree(pidlParent);
        return;
    }

    SendMessageW( info->hwndTreeView, TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT );
    item = InsertTreeViewItem( info, lpsfParent, pidlChild,
                               pidlParent, pEnumChildren, TVI_ROOT );
    SendMessageW( info->hwndTreeView, TVM_EXPAND, TVE_EXPAND, (LPARAM)item );

    ILFree(pidlChild);
    ILFree(pidlParent);
    IShellFolder_Release(lpsfRoot);
    IShellFolder_Release(lpsfParent);
}