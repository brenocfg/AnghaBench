#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i; int /*<<< orphan*/  f; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_5__ {scalar_t__ base; int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 scalar_t__ IDC_RADIO_DEC ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _finite (int /*<<< orphan*/ ) ; 
 TYPE_3__ calc ; 

void rpn_exp2(calc_number_t *c)
{
    if (calc.base == IDC_RADIO_DEC) {
        c->f *= c->f;
        if (_finite(c->f) == 0)
            calc.is_nan = TRUE;
    } else
        c->i *= c->i;
}