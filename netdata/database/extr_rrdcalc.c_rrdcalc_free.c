#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  spdim; struct TYPE_4__* info; struct TYPE_4__* units; struct TYPE_4__* source; struct TYPE_4__* recipient; struct TYPE_4__* exec; struct TYPE_4__* foreachdim; struct TYPE_4__* dimensions; struct TYPE_4__* family; struct TYPE_4__* chart; struct TYPE_4__* name; int /*<<< orphan*/  critical; int /*<<< orphan*/  warning; int /*<<< orphan*/  calculation; } ;
typedef  TYPE_1__ RRDCALC ;

/* Variables and functions */
 int /*<<< orphan*/  expression_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_pattern_free (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void rrdcalc_free(RRDCALC *rc) {
    if(unlikely(!rc)) return;

    expression_free(rc->calculation);
    expression_free(rc->warning);
    expression_free(rc->critical);

    freez(rc->name);
    freez(rc->chart);
    freez(rc->family);
    freez(rc->dimensions);
    freez(rc->foreachdim);
    freez(rc->exec);
    freez(rc->recipient);
    freez(rc->source);
    freez(rc->units);
    freez(rc->info);
    simple_pattern_free(rc->spdim);
    freez(rc);
}