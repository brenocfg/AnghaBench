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
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/ * HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CharToOem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEY_READ ; 
 int /*<<< orphan*/  ProcessHeap ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ *) ; 
 scalar_t__ RegOpenKeyEx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ RegQueryValueEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * _T (char*) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wsprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

LPTSTR GetConnectionType(LPTSTR lpClass)
{
    HKEY hKey = NULL;
    LPTSTR ConType = NULL;
    LPTSTR ConTypeTmp = NULL;
    TCHAR Path[256];
    LPTSTR PrePath  = _T("SYSTEM\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}\\");
    LPTSTR PostPath = _T("\\Connection");
    DWORD PathSize;
    DWORD dwType;
    DWORD dwDataSize;

    /* don't overflow the buffer */
    PathSize = lstrlen(PrePath) + lstrlen(lpClass) + lstrlen(PostPath) + 1;
    if (PathSize >= 255)
        return NULL;

    wsprintf(Path, _T("%s%s%s"), PrePath, lpClass, PostPath);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     Path,
                     0,
                     KEY_READ,
                     &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueEx(hKey,
                            _T("Name"),
                            NULL,
                            &dwType,
                            NULL,
                            &dwDataSize) == ERROR_SUCCESS)
        {
            ConTypeTmp = (LPTSTR)HeapAlloc(ProcessHeap,
                                           0,
                                           dwDataSize);

            if (ConTypeTmp == NULL)
                return NULL;
                                        
            ConType = (LPTSTR)HeapAlloc(ProcessHeap,
                                        0,
                                        dwDataSize);

            if (ConType == NULL)
            {
                HeapFree(ProcessHeap, 0, ConTypeTmp);
                return NULL;
            }

            if (RegQueryValueEx(hKey,
                                _T("Name"),
                                NULL,
                                &dwType,
                                (PBYTE)ConTypeTmp,
                                &dwDataSize) != ERROR_SUCCESS)
            {
                HeapFree(ProcessHeap,
                         0,
                         ConType);

                ConType = NULL;
            }

            if (ConType)
                CharToOem(ConTypeTmp, ConType);
            HeapFree(ProcessHeap, 0, ConTypeTmp);
        }
    }

    if (hKey != NULL)
        RegCloseKey(hKey);

    return ConType;
}