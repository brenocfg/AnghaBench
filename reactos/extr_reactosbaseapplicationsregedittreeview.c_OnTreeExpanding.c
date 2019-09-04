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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int state; scalar_t__ hItem; } ;
struct TYPE_5__ {TYPE_1__ itemNew; } ;
typedef  TYPE_2__ NMTREEVIEW ;
typedef  scalar_t__* LPWSTR ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AddEntryToTree (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int FALSE ; 
 scalar_t__* GetItemPath (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IDC_WAIT ; 
 int /*<<< orphan*/  KEY_QUERY_VALUE ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  LoadCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,scalar_t__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegOpenKeyExW (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int TVIS_EXPANDEDONCE ; 
 int /*<<< orphan*/  TVM_SORTCHILDREN ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

BOOL OnTreeExpanding(HWND hwndTV, NMTREEVIEW* pnmtv)
{
    DWORD dwCount, dwIndex, dwMaxSubKeyLen;
    HKEY hRoot, hNewKey, hKey;
    LPCWSTR keyPath;
    LPWSTR Name;
    LONG errCode;
    HCURSOR hcursorOld;

    static int expanding;
    if (expanding) return FALSE;
    if (pnmtv->itemNew.state & TVIS_EXPANDEDONCE )
    {
        return TRUE;
    }
    expanding = TRUE;
    hcursorOld = SetCursor(LoadCursor(NULL, IDC_WAIT));
    SendMessageW(hwndTV, WM_SETREDRAW, FALSE, 0);

    keyPath = GetItemPath(hwndTV, pnmtv->itemNew.hItem, &hRoot);
    if (!keyPath) goto done;

    if (*keyPath)
    {
        errCode = RegOpenKeyExW(hRoot, keyPath, 0, KEY_READ, &hNewKey);
        if (errCode != ERROR_SUCCESS) goto done;
    }
    else
    {
        hNewKey = hRoot;
    }

    errCode = RegQueryInfoKeyW(hNewKey, 0, 0, 0, &dwCount, &dwMaxSubKeyLen, 0, 0, 0, 0, 0, 0);
    if (errCode != ERROR_SUCCESS) goto done;
    dwMaxSubKeyLen++; /* account for the \0 terminator */
    Name = HeapAlloc(GetProcessHeap(), 0, dwMaxSubKeyLen * sizeof(WCHAR));
    if (!Name) goto done;

    for (dwIndex = 0; dwIndex < dwCount; dwIndex++)
    {
        DWORD cName = dwMaxSubKeyLen, dwSubCount;

        errCode = RegEnumKeyExW(hNewKey, dwIndex, Name, &cName, 0, 0, 0, 0);
        if (errCode != ERROR_SUCCESS) continue;
        errCode = RegOpenKeyExW(hNewKey, Name, 0, KEY_QUERY_VALUE, &hKey);
        if (errCode == ERROR_SUCCESS)
        {
            errCode = RegQueryInfoKeyW(hKey, 0, 0, 0, &dwSubCount, 0, 0, 0, 0, 0, 0, 0);
            RegCloseKey(hKey);
        }
        if (errCode != ERROR_SUCCESS) dwSubCount = 0;
        AddEntryToTree(hwndTV, pnmtv->itemNew.hItem, Name, NULL, dwSubCount);
    }

    SendMessageW(hwndTV, TVM_SORTCHILDREN, 0, (LPARAM)pnmtv->itemNew.hItem);

    RegCloseKey(hNewKey);
    HeapFree(GetProcessHeap(), 0, Name);

done:
    SendMessageW(hwndTV, WM_SETREDRAW, TRUE, 0);
    SetCursor(hcursorOld);
    expanding = FALSE;

    return TRUE;
}