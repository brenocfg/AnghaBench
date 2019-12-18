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
typedef  int /*<<< orphan*/  STRRET ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  LPSHELLFOLDER ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IShellFolder_GetDisplayNameOf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  SHGDN_FORPARSING ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrRetToBufW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL COMDLG32_GetDisplayNameOf(LPCITEMIDLIST pidl, LPWSTR pwszPath) {
    LPSHELLFOLDER psfDesktop;
    STRRET strret;
        
    if (FAILED(SHGetDesktopFolder(&psfDesktop)))
        return FALSE;

    if (FAILED(IShellFolder_GetDisplayNameOf(psfDesktop, pidl, SHGDN_FORPARSING, &strret))) {
        IShellFolder_Release(psfDesktop);
        return FALSE;
    }

    IShellFolder_Release(psfDesktop);
    return SUCCEEDED(StrRetToBufW(&strret, pidl, pwszPath, MAX_PATH));
}