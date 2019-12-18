#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WCHAR ;
struct TYPE_3__ {int fAnyOperationsAborted; int /*<<< orphan*/  fFlags; int /*<<< orphan*/ * pTo; scalar_t__* pFrom; int /*<<< orphan*/  wFunc; int /*<<< orphan*/ * hwnd; } ;
typedef  TYPE_1__ SHFILEOPSTRUCTW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ,int) ; 
 int FALSE ; 
 int /*<<< orphan*/  FOF_NOCONFIRMATION ; 
 int /*<<< orphan*/  FO_DELETE ; 
 int MAX_PATH ; 
 int SHFileOperationW (TYPE_1__*) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,int /*<<< orphan*/ ) ; 
 int strlenW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL cache_container_delete_dir(LPCWSTR lpszPath)
{
    DWORD path_len;
    WCHAR path[MAX_PATH + 1];
    SHFILEOPSTRUCTW shfos;
    int ret;

    path_len = strlenW(lpszPath);
    if (path_len >= MAX_PATH)
        return FALSE;
    strcpyW(path, lpszPath);
    path[path_len + 1] = 0;  /* double-NUL-terminate path */

    shfos.hwnd = NULL;
    shfos.wFunc = FO_DELETE;
    shfos.pFrom = path;
    shfos.pTo = NULL;
    shfos.fFlags = FOF_NOCONFIRMATION;
    shfos.fAnyOperationsAborted = FALSE;
    ret = SHFileOperationW(&shfos);
    if (ret)
        ERR("SHFileOperationW on %s returned %i\n", debugstr_w(path), ret);
    return !(ret || shfos.fAnyOperationsAborted);
}