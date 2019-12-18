#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; double min; double max; double sum; double sum2; } ;
typedef  TYPE_1__ SimpleStats ;

/* Variables and functions */

__attribute__((used)) static void
addToSimpleStats(SimpleStats *ss, double val)
{
	if (ss->count == 0 || val < ss->min)
		ss->min = val;
	if (ss->count == 0 || val > ss->max)
		ss->max = val;
	ss->count++;
	ss->sum += val;
	ss->sum2 += val * val;
}