#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i; } ;
typedef  TYPE_1__ calc_number_t ;
struct TYPE_7__ {int /*<<< orphan*/  is_nan; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_5__ calc ; 

__attribute__((used)) static void rpn_mod_i(calc_number_t *r, calc_number_t *a, calc_number_t *b)
{
    if (b->i == 0)
        calc.is_nan = TRUE;
    else
        r->i = a->i % b->i;
}