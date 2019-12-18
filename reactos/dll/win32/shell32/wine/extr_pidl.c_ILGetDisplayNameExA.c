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
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  LPSHELLFOLDER ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ILGetDisplayNameExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL ILGetDisplayNameExA(LPSHELLFOLDER psf, LPCITEMIDLIST pidl, LPSTR path, DWORD type)
{
    BOOL ret = FALSE;
    WCHAR wPath[MAX_PATH];

    TRACE("%p %p %p %d\n", psf, pidl, path, type);

    if (!pidl || !path)
        return FALSE;

    ret = ILGetDisplayNameExW(psf, pidl, wPath, type);
    WideCharToMultiByte(CP_ACP, 0, wPath, -1, path, MAX_PATH, NULL, NULL);
    TRACE("%p %p %s\n", psf, pidl, debugstr_a(path));

    return ret;
}