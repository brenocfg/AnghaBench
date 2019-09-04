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
struct TYPE_2__ {scalar_t__ buffer; scalar_t__ ptr; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tcscmp (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__ calc ; 
 int /*<<< orphan*/  convert_text2number_2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpn_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpn_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void convert_text2number(calc_number_t *a)
{
    /* if the screen output buffer is empty, then */
    /* the operand is taken from the last input */
    if (calc.buffer == calc.ptr) {
        /* if pushed valued is ZERO then we should grab it */
        if (!_tcscmp(calc.buffer, _T("0.")) ||
            !_tcscmp(calc.buffer, _T("0")))
            /* this zero is good for both integer and decimal */
            rpn_zero(a);
        else
            rpn_copy(a, &calc.code);
        return;
    }
    /* ZERO is the default value for all numeric bases */
    rpn_zero(a);
    convert_text2number_2(a);
}