#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {double f; scalar_t__ i; } ;
typedef  TYPE_1__ calc_number_t ;
typedef  scalar_t__ __int64 ;
struct TYPE_6__ {scalar_t__ base; void* is_nan; } ;

/* Variables and functions */
 scalar_t__ IDC_RADIO_DEC ; 
 void* TRUE ; 
 scalar_t__ _finite (double) ; 
 TYPE_4__ calc ; 
 int /*<<< orphan*/  rpn_int (TYPE_1__*) ; 

void rpn_fact(calc_number_t *c)
{
    double fact, mult, num;

    if (calc.base == IDC_RADIO_DEC)
        num = c->f;
    else
        num = (double)c->i;
    if (num > 1000) {
        calc.is_nan = TRUE;
        return;
    }
    if (num < 0) {
        calc.is_nan = TRUE;
        return;
    } else
    if (num == 0)
        fact = 1;
    else {
        rpn_int(c);
        fact = 1;
        mult = 2;
        while (mult <= num) {
            fact *= mult;
            mult++;
        }
        c->f = fact;
    }
    if (_finite(fact) == 0)
        calc.is_nan = TRUE;
    else
    if (calc.base == IDC_RADIO_DEC)
        c->f = fact;
    else
        c->i = (__int64)fact;
}