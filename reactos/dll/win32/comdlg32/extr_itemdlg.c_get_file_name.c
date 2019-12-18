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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int UINT ;
struct TYPE_3__ {scalar_t__ set_filename; int /*<<< orphan*/  dlg_hwnd; } ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ FileDialogImpl ;

/* Variables and functions */
 scalar_t__ CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_FILENAME ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_GETTEXT ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__,scalar_t__) ; 
 int lstrlenW (scalar_t__) ; 

__attribute__((used)) static UINT get_file_name(FileDialogImpl *This, LPWSTR *str)
{
    HWND hwnd_edit = GetDlgItem(This->dlg_hwnd, IDC_FILENAME);
    UINT len;

    if(!hwnd_edit)
    {
        if(This->set_filename)
        {
            len = lstrlenW(This->set_filename);
            *str = CoTaskMemAlloc(sizeof(WCHAR)*(len+1));
            lstrcpyW(*str, This->set_filename);
            return len;
        }
        return 0;
    }

    len = SendMessageW(hwnd_edit, WM_GETTEXTLENGTH, 0, 0);
    *str = CoTaskMemAlloc(sizeof(WCHAR)*(len+1));
    if(!*str)
        return 0;

    SendMessageW(hwnd_edit, WM_GETTEXT, len+1, (LPARAM)*str);
    return len;
}