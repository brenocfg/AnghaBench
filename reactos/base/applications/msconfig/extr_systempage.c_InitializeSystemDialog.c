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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowsDirectoryW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LoadSystemIni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PATH_MAX ; 

__attribute__((used)) static BOOL
InitializeSystemDialog(HWND hDlg)
{
    WCHAR winDir[PATH_MAX];

    GetWindowsDirectoryW(winDir, PATH_MAX);
    return LoadSystemIni(winDir, hDlg);
}