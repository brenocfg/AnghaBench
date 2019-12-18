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
struct TYPE_4__ {int zone; scalar_t__ time; } ;
typedef  TYPE_1__ TimeTzADT ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  TimeTzADTPGetDatum (TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 

__attribute__((used)) static Datum
leftmostvalue_timetz(void)
{
	TimeTzADT  *v = palloc(sizeof(TimeTzADT));

	v->time = 0;
	v->zone = -24 * 3600;		/* XXX is that true? */

	return TimeTzADTPGetDatum(v);
}