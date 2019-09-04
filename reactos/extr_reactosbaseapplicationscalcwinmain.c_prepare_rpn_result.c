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
struct TYPE_2__ {int /*<<< orphan*/  hInstance; int /*<<< orphan*/  code; scalar_t__ is_nan; } ;
typedef  int /*<<< orphan*/  TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  IDS_MATH_ERROR ; 
 int /*<<< orphan*/  LoadString (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ calc ; 
 int /*<<< orphan*/  prepare_rpn_result_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rpn_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void prepare_rpn_result(calc_number_t *rpn, TCHAR *buffer, int size, int base)
{
    if (calc.is_nan) {
        rpn_zero(&calc.code);
        LoadString(calc.hInstance, IDS_MATH_ERROR, buffer, size);
        return;
    }
    prepare_rpn_result_2(rpn, buffer, size, base);
}