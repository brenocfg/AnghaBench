#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_5__ {unsigned int base; unsigned int degr; unsigned int size; int /*<<< orphan*/  hInstance; int /*<<< orphan*/  code; } ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  idc; } ;
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HMENU ;

/* Variables and functions */
 int BITMASK_BIN_MASK ; 
 int BITMASK_DEC_MASK ; 
 int BITMASK_HEX_MASK ; 
 int BITMASK_OCT_MASK ; 
 int /*<<< orphan*/  CheckRadioButton (int /*<<< orphan*/ ,int const,int const,unsigned int) ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMenu (int /*<<< orphan*/ ) ; 
#define  IDC_RADIO_BIN 131 
 int const IDC_RADIO_BYTE ; 
#define  IDC_RADIO_DEC 130 
 int const IDC_RADIO_DEG ; 
 int const IDC_RADIO_GRAD ; 
#define  IDC_RADIO_HEX 129 
#define  IDC_RADIO_OCT 128 
 int const IDC_RADIO_QWORD ; 
 int /*<<< orphan*/  IDR_MENU_SCIENTIFIC_1 ; 
 int /*<<< orphan*/  IDR_MENU_SCIENTIFIC_2 ; 
 int /*<<< orphan*/  LoadMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCE (int /*<<< orphan*/ ) ; 
 int SIZEOF (TYPE_1__*) ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 int /*<<< orphan*/  SetMenu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ calc ; 
 int /*<<< orphan*/  convert_real_integer (unsigned int) ; 
 int /*<<< orphan*/  convert_text2number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_rpn_result (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_allowed_controls (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* radio_setup ; 
 int /*<<< orphan*/  update_menu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_radio(HWND hwnd, unsigned int base)
{
    HMENU   hMenu;
    LPCTSTR lpMenuId;
    WORD    mask;
    int     n;

    switch (base) {
    case IDC_RADIO_DEC:
        lpMenuId = MAKEINTRESOURCE(IDR_MENU_SCIENTIFIC_1);
        mask = BITMASK_DEC_MASK;
        break;
    case IDC_RADIO_HEX:
        lpMenuId = MAKEINTRESOURCE(IDR_MENU_SCIENTIFIC_2);
        mask = BITMASK_HEX_MASK;
        break;
    case IDC_RADIO_OCT:
        lpMenuId = MAKEINTRESOURCE(IDR_MENU_SCIENTIFIC_2);
        mask = BITMASK_OCT_MASK;
        break;
    case IDC_RADIO_BIN:
        lpMenuId = MAKEINTRESOURCE(IDR_MENU_SCIENTIFIC_2);
        mask = BITMASK_BIN_MASK;
        break;
    default:
        return;
    }

    if (calc.base != base) {
        convert_text2number(&calc.code);
        convert_real_integer(base);
        calc.base = base;
        display_rpn_result(hwnd, &calc.code);

        hMenu = GetMenu(hwnd);
        DestroyMenu(hMenu);
        hMenu = LoadMenu(calc.hInstance, lpMenuId);
        SetMenu(hwnd, hMenu);
        update_menu(hwnd);

        for (n=0; n<SIZEOF(radio_setup); n++)
            ShowWindow(GetDlgItem(hwnd, radio_setup[n].idc), (radio_setup[n].mask & mask) ? SW_SHOW : SW_HIDE);

        enable_allowed_controls(hwnd, base);
    }

    CheckRadioButton(hwnd, IDC_RADIO_HEX, IDC_RADIO_BIN, calc.base);

    if (base == IDC_RADIO_DEC)
        CheckRadioButton(hwnd, IDC_RADIO_DEG, IDC_RADIO_GRAD, calc.degr);
    else
        CheckRadioButton(hwnd, IDC_RADIO_QWORD, IDC_RADIO_BYTE, calc.size);
}