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
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_3__ {int right; int left; } ;
typedef  TYPE_1__ RECT ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HDC ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CreateCompatibleDC (scalar_t__) ; 
 int /*<<< orphan*/  DeleteDC (scalar_t__) ; 
 int /*<<< orphan*/  EM_SETTARGETDEVICE ; 
 scalar_t__ GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_EDITOR ; 
 scalar_t__ ID_WORDWRAP_MARGIN ; 
 scalar_t__ ID_WORDWRAP_NONE ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ get_print_rect (scalar_t__) ; 
 scalar_t__ make_dc () ; 

void target_device(HWND hMainWnd, DWORD wordWrap)
{
    HWND hEditorWnd = GetDlgItem(hMainWnd, IDC_EDITOR);

    if(wordWrap == ID_WORDWRAP_MARGIN)
    {
        int width = 0;
        LRESULT result;
        HDC hdc = make_dc();
        RECT rc = get_print_rect(hdc);

        width = rc.right - rc.left;
        if(!hdc)
        {
            HDC hMaindc = GetDC(hMainWnd);
            hdc = CreateCompatibleDC(hMaindc);
            ReleaseDC(hMainWnd, hMaindc);
        }
        result = SendMessageW(hEditorWnd, EM_SETTARGETDEVICE, (WPARAM)hdc, width);
        DeleteDC(hdc);
        if (result)
            return;
        /* otherwise EM_SETTARGETDEVICE failed, so fall back on wrapping
         * to window using the NULL DC. */
    }

    if (wordWrap != ID_WORDWRAP_NONE) {
        SendMessageW(hEditorWnd, EM_SETTARGETDEVICE, 0, 0);
    } else {
        SendMessageW(hEditorWnd, EM_SETTARGETDEVICE, 0, 1);
    }

}