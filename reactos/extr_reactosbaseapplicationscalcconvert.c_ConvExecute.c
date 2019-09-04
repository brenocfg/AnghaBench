#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ formula_to; scalar_t__ formula_from; scalar_t__ unit; } ;
typedef  TYPE_2__ conv_t ;
struct TYPE_13__ {TYPE_1__* Convert; int /*<<< orphan*/  hInstance; } ;
struct TYPE_12__ {TYPE_2__* items; scalar_t__ category; } ;
struct TYPE_10__ {char* data; int /*<<< orphan*/  wm_msg; } ;
typedef  TYPE_3__ TCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CB_GETCURSEL ; 
 int /*<<< orphan*/  CB_GETLBTEXT ; 
 int /*<<< orphan*/  IDC_COMBO_CATEGORY ; 
 int /*<<< orphan*/  IDC_COMBO_FROM ; 
 int /*<<< orphan*/  IDC_COMBO_TO ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SIZEOF (TYPE_3__*) ; 
 size_t SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_HANDLE_FROM ; 
 int /*<<< orphan*/  WM_HANDLE_TO ; 
 int /*<<< orphan*/  WM_START_CONV ; 
 int /*<<< orphan*/  _tcscmp (TYPE_3__*,TYPE_3__*) ; 
 TYPE_5__ calc ; 
 TYPE_3__* conv_table ; 

void ConvExecute(HWND hWnd)
{
    DWORD         c_cat = (DWORD)SendDlgItemMessage(hWnd, IDC_COMBO_CATEGORY, CB_GETCURSEL, 0, 0);
    const conv_t *items = NULL;
    DWORD         from  = SendDlgItemMessage(hWnd, IDC_COMBO_FROM, CB_GETCURSEL, 0, 0);
    DWORD         to    = SendDlgItemMessage(hWnd, IDC_COMBO_TO,   CB_GETCURSEL, 0, 0);
    TCHAR         txt_cb[128];
    TCHAR         txt[128];
    const conv_t *item;

    /* do nothing if the indexes point to the same unit */
    if (from == to)
        return;

    /* Search correct category, since it can be sorted too */
    SendDlgItemMessage(hWnd, IDC_COMBO_CATEGORY, CB_GETLBTEXT, c_cat, (LPARAM)txt_cb);
    for (c_cat=0; c_cat < SIZEOF(conv_table); c_cat++) {
        LoadString(calc.hInstance, conv_table[c_cat].category, txt, SIZEOF(txt));
        if (!_tcscmp(txt_cb, txt)) {
            items = conv_table[c_cat].items;
            break;
        }
    }

    /* The units can be sorted, so I must search the exact match */
    item = items;
    SendDlgItemMessage(hWnd, IDC_COMBO_FROM, CB_GETLBTEXT, from, (LPARAM)txt_cb);
    while (item->unit) {
        LoadString(calc.hInstance, item->unit, txt, SIZEOF(txt));
        if (!_tcscmp(txt_cb, txt)) {
            from = item-items;
            break;
        }
        item++;
    }
    SendDlgItemMessage(hWnd, IDC_COMBO_TO, CB_GETLBTEXT, to, (LPARAM)txt_cb);
    item = items;
    while (item->unit) {
        LoadString(calc.hInstance, item->unit, txt, SIZEOF(txt));
        if (!_tcscmp(txt_cb, txt)) {
            to = item-items;
            break;
        }
        item++;
    }

    calc.Convert[0].data = (char *)items[from].formula_from;
    calc.Convert[1].data = (char *)items[to].formula_to;
    calc.Convert[0].wm_msg = WM_HANDLE_FROM;
    calc.Convert[1].wm_msg = WM_HANDLE_TO;
    PostMessage(hWnd, WM_START_CONV, 0, MAKELPARAM(0, WM_HANDLE_FROM));
}