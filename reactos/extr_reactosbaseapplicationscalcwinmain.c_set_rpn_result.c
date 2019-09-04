#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  calc_number_t ;
struct TYPE_2__ {scalar_t__ buffer; scalar_t__ ptr; int /*<<< orphan*/  base; int /*<<< orphan*/  sci_in; } ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SIZEOF (scalar_t__) ; 
 scalar_t__ _tcslen (scalar_t__) ; 
 TYPE_1__ calc ; 
 int /*<<< orphan*/  prepare_rpn_result (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_lcd_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_parent_display (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_rpn_result(HWND hwnd, calc_number_t *rpn)
{
    calc.sci_in = FALSE;
    prepare_rpn_result(rpn, calc.buffer, SIZEOF(calc.buffer), calc.base);
    calc.ptr = calc.buffer + _tcslen(calc.buffer);
    update_lcd_display(hwnd);
    update_parent_display(hwnd);
}