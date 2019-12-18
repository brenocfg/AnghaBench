#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hInstance; } ;
struct TYPE_6__ {int /*<<< orphan*/  category; } ;
typedef  TYPE_1__ TCHAR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  CB_ADDSTRING ; 
 int /*<<< orphan*/  CB_SETCURSEL ; 
 int /*<<< orphan*/  ConvAdjust (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COMBO_CATEGORY ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 
 unsigned int SIZEOF (TYPE_1__*) ; 
 int /*<<< orphan*/  SendMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ calc ; 
 TYPE_1__* conv_table ; 

void ConvInit(HWND hWnd)
{
    HWND         hCatWnd = GetDlgItem(hWnd, IDC_COMBO_CATEGORY);
    TCHAR        txt[128];
    unsigned int n;

    /* Fill category combo */
    for (n=0; n<SIZEOF(conv_table); n++) {
        LoadString(calc.hInstance, conv_table[n].category, txt, SIZEOF(txt));
        SendMessage(hCatWnd, CB_ADDSTRING, 0, (LPARAM)txt);
    }
    SendMessage(hCatWnd, CB_SETCURSEL, 0, 0);
    ConvAdjust(hWnd, 0);
}