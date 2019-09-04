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
struct TYPE_5__ {long double f; scalar_t__ i; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_6__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IDC_RADIO_DEC ; 
 TYPE_4__ calc ; 
 scalar_t__ logic_dbl2int (TYPE_1__*) ; 

void rpn_not(calc_number_t *c)
{
    if (calc.base == IDC_RADIO_DEC) {
        calc_number_t n;
        n.i = logic_dbl2int(c);
        c->f = (long double)(~n.i);
    } else
        c->i = ~c->i;
}