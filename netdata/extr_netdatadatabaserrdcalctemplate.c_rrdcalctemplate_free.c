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
struct TYPE_4__ {struct TYPE_4__* dimensions; struct TYPE_4__* info; struct TYPE_4__* units; struct TYPE_4__* source; struct TYPE_4__* context; struct TYPE_4__* recipient; struct TYPE_4__* exec; struct TYPE_4__* name; int /*<<< orphan*/  family_pattern; struct TYPE_4__* family_match; int /*<<< orphan*/  critical; int /*<<< orphan*/  warning; int /*<<< orphan*/  calculation; } ;
typedef  TYPE_1__ RRDCALCTEMPLATE ;

/* Variables and functions */
 int /*<<< orphan*/  expression_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freez (TYPE_1__*) ; 
 int /*<<< orphan*/  simple_pattern_free (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

inline void rrdcalctemplate_free(RRDCALCTEMPLATE *rt) {
    if(unlikely(!rt)) return;

    expression_free(rt->calculation);
    expression_free(rt->warning);
    expression_free(rt->critical);

    freez(rt->family_match);
    simple_pattern_free(rt->family_pattern);

    freez(rt->name);
    freez(rt->exec);
    freez(rt->recipient);
    freez(rt->context);
    freez(rt->source);
    freez(rt->units);
    freez(rt->info);
    freez(rt->dimensions);
    freez(rt);
}