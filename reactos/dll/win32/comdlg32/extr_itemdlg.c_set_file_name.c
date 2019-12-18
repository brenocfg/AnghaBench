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
struct TYPE_3__ {int /*<<< orphan*/ * set_filename; int /*<<< orphan*/  dlg_hwnd; } ;
typedef  scalar_t__ LPCWSTR ;
typedef  TYPE_1__ FileDialogImpl ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  IDC_FILENAME ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDlgItemTextW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * StrDupW (scalar_t__) ; 

__attribute__((used)) static BOOL set_file_name(FileDialogImpl *This, LPCWSTR str)
{
    if(This->set_filename)
        LocalFree(This->set_filename);

    This->set_filename = str ? StrDupW(str) : NULL;

    return SetDlgItemTextW(This->dlg_hwnd, IDC_FILENAME, This->set_filename);
}