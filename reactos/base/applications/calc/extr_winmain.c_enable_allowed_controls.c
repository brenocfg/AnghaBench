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
struct TYPE_5__ {int /*<<< orphan*/  hStatWnd; } ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  idc; } ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int DWORD ;
typedef  int BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int BITMASK_BIN_MASK ; 
 int BITMASK_DEC_MASK ; 
 int BITMASK_HEX_MASK ; 
 int BITMASK_IS_STATS ; 
 int BITMASK_OCT_MASK ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IDC_RADIO_BIN 131 
#define  IDC_RADIO_DEC 130 
#define  IDC_RADIO_HEX 129 
#define  IDC_RADIO_OCT 128 
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ IsWindowEnabled (int /*<<< orphan*/ ) ; 
 int SIZEOF (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 TYPE_2__ calc ; 
 TYPE_1__* key2code ; 

__attribute__((used)) static void enable_allowed_controls(HWND hwnd, DWORD base)
{
    BYTE mask;
    int  n;

    switch (base) {
    case IDC_RADIO_DEC:
        mask = BITMASK_DEC_MASK;
        break;
    case IDC_RADIO_HEX:
        mask = BITMASK_HEX_MASK;
        break;
    case IDC_RADIO_OCT:
        mask = BITMASK_OCT_MASK;
        break;
    case IDC_RADIO_BIN:
        mask = BITMASK_BIN_MASK;
        break;
    default:
        return;
    }
    for (n=0; n<SIZEOF(key2code); n++) {
        if (key2code[n].mask != 0) {
            HWND hCtlWnd = GetDlgItem(hwnd, key2code[n].idc);
            BOOL current;

            if ((key2code[n].mask & BITMASK_IS_STATS))
                current = IsWindow(calc.hStatWnd) ? TRUE : FALSE;
            else
                current = (key2code[n].mask & mask) ? TRUE : FALSE;
            if (IsWindowEnabled(hCtlWnd) != current)
                EnableWindow(hCtlWnd, current);
        }
    }
}