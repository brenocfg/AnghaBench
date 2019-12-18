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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int cChildren; int cchTextMax; int* pszText; void* hItem; int /*<<< orphan*/  mask; } ;
typedef  TYPE_1__ TVITEMW ;
typedef  int* LPWSTR ;
typedef  int* LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  void* HTREEITEM ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddEntryToTree (int /*<<< orphan*/ ,void*,int*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int* GetItemPath (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TVIF_CHILDREN ; 
 int /*<<< orphan*/  TVIF_TEXT ; 
 int /*<<< orphan*/  TVIS_EXPANDED ; 
 int /*<<< orphan*/  TVM_SORTCHILDREN ; 
 int /*<<< orphan*/  TreeView_DeleteItem (int /*<<< orphan*/ ,void*) ; 
 void* TreeView_GetChild (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TreeView_GetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ TreeView_GetItemState (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 void* TreeView_GetNextSibling (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  TreeView_SetItem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wcscmp (int*,int*) ; 
 scalar_t__ wcslen (int*) ; 

BOOL RefreshTreeItem(HWND hwndTV, HTREEITEM hItem)
{
    HKEY hRoot, hKey, hSubKey;
    HTREEITEM childItem;
    LPCWSTR KeyPath;
    DWORD dwCount, dwIndex, dwMaxSubKeyLen;
    LPWSTR Name = NULL;
    TVITEMW tvItem;
    LPWSTR pszNodes = NULL;
    BOOL bSuccess = FALSE;
    LPWSTR s;
    BOOL bAddedAny;

    KeyPath = GetItemPath(hwndTV, hItem, &hRoot);

    if (*KeyPath)
    {
        if (RegOpenKeyExW(hRoot, KeyPath, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
        {
            goto done;
        }
    }
    else
    {
        hKey = hRoot;
    }

    if (RegQueryInfoKeyW(hKey, 0, 0, 0, &dwCount, &dwMaxSubKeyLen, 0, 0, 0, 0, 0, 0) != ERROR_SUCCESS)
    {
        goto done;
    }

    /* Set the number of children again */
    tvItem.mask = TVIF_CHILDREN;
    tvItem.hItem = hItem;
    tvItem.cChildren = dwCount;
    if (!TreeView_SetItem(hwndTV, &tvItem))
    {
        goto done;
    }

    /* We don't have to bother with the rest if it's not expanded. */
    if (TreeView_GetItemState(hwndTV, hItem, TVIS_EXPANDED) == 0)
    {
        RegCloseKey(hKey);
        bSuccess = TRUE;
        goto done;
    }

    dwMaxSubKeyLen++; /* account for the \0 terminator */
    if (!(Name = HeapAlloc(GetProcessHeap(), 0, dwMaxSubKeyLen * sizeof(WCHAR))))
    {
        goto done;
    }
    tvItem.cchTextMax = dwMaxSubKeyLen;
    /*if (!(tvItem.pszText = HeapAlloc(GetProcessHeap(), 0, dwMaxSubKeyLen * sizeof(WCHAR)))) {
        goto done;
    }*/

    /* Get all of the tree node siblings in one contiguous block of memory */
    {
        DWORD dwPhysicalSize = 0;
        DWORD dwActualSize = 0;
        DWORD dwNewPhysicalSize;
        LPWSTR pszNewNodes;
        DWORD dwStep = 10000;

        for (childItem = TreeView_GetChild(hwndTV, hItem); childItem;
                childItem = TreeView_GetNextSibling(hwndTV, childItem))
        {

            if (dwActualSize + dwMaxSubKeyLen + 1 > dwPhysicalSize)
            {
                dwNewPhysicalSize = dwActualSize + dwMaxSubKeyLen + 1 + dwStep;

                if (pszNodes)
                    pszNewNodes = (LPWSTR) HeapReAlloc(GetProcessHeap(), 0, pszNodes, dwNewPhysicalSize * sizeof(WCHAR));
                else
                    pszNewNodes = (LPWSTR) HeapAlloc(GetProcessHeap(), 0, dwNewPhysicalSize * sizeof(WCHAR));
                if (!pszNewNodes)
                    goto done;

                dwPhysicalSize = dwNewPhysicalSize;
                pszNodes = pszNewNodes;
            }

            tvItem.mask = TVIF_TEXT;
            tvItem.hItem = childItem;
            tvItem.pszText = &pszNodes[dwActualSize];
            tvItem.cchTextMax = dwPhysicalSize - dwActualSize;
            if (!TreeView_GetItem(hwndTV, &tvItem))
                goto done;

            dwActualSize += (DWORD) wcslen(&pszNodes[dwActualSize]) + 1;
        }

        if (pszNodes)
            pszNodes[dwActualSize] = L'\0';
    }

    /* Now go through all the children in the tree, and check if any have to be removed. */
    childItem = TreeView_GetChild(hwndTV, hItem);
    while (childItem)
    {
        HTREEITEM nextItem = TreeView_GetNextSibling(hwndTV, childItem);
        if (RefreshTreeItem(hwndTV, childItem) == FALSE)
        {
            (void)TreeView_DeleteItem(hwndTV, childItem);
        }
        childItem = nextItem;
    }

    /* Now go through all the children in the registry, and check if any have to be added. */
    bAddedAny = FALSE;
    for (dwIndex = 0; dwIndex < dwCount; dwIndex++)
    {
        DWORD cName = dwMaxSubKeyLen, dwSubCount;
        BOOL found;

        found = FALSE;
        if (RegEnumKeyExW(hKey, dwIndex, Name, &cName, 0, 0, 0, NULL) != ERROR_SUCCESS)
        {
            continue;
        }

        /* Check if the node is already in there. */
        if (pszNodes)
        {
            for (s = pszNodes; *s; s += wcslen(s) + 1)
            {
                if (!wcscmp(s, Name))
                {
                    found = TRUE;
                    break;
                }
            }
        }

        if (found == FALSE)
        {
            /* Find the number of children of the node. */
            dwSubCount = 0;
            if (RegOpenKeyExW(hKey, Name, 0, KEY_QUERY_VALUE, &hSubKey) == ERROR_SUCCESS)
            {
                if (RegQueryInfoKeyW(hSubKey, 0, 0, 0, &dwSubCount, 0, 0, 0, 0, 0, 0, 0) != ERROR_SUCCESS)
                {
                    dwSubCount = 0;
                }
                RegCloseKey(hSubKey);
            }

            AddEntryToTree(hwndTV, hItem, Name, NULL, dwSubCount);
            bAddedAny = TRUE;
        }
    }
    RegCloseKey(hKey);

    if (bAddedAny)
        SendMessageW(hwndTV, TVM_SORTCHILDREN, 0, (LPARAM) hItem);

    bSuccess = TRUE;

done:
    if (pszNodes)
        HeapFree(GetProcessHeap(), 0, pszNodes);
    if (Name)
        HeapFree(GetProcessHeap(), 0, Name);
    return bSuccess;
}