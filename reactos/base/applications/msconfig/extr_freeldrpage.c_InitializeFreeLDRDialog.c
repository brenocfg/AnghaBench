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
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (int*,int) ; 
 int /*<<< orphan*/  LoadBootIni (int*,int /*<<< orphan*/ ) ; 
 int PATH_MAX ; 
 int* wcschr (int*,int) ; 

__attribute__((used)) static BOOL
InitializeFreeLDRDialog(HWND hDlg)
{
    WCHAR winDir[PATH_MAX];
    WCHAR* ptr = NULL;

    GetWindowsDirectoryW(winDir, PATH_MAX);
    ptr = wcschr(winDir, L'\\');
    if (ptr == NULL)
    {
        return FALSE;
    }
    ptr[1] = L'\0';
    return LoadBootIni(winDir, hDlg);
}