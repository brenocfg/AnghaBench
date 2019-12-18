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
typedef  int /*<<< orphan*/  timestamp ;
struct TYPE_4__ {int /*<<< orphan*/  time; int /*<<< orphan*/  month; } ;
typedef  TYPE_1__ interval ;

/* Variables and functions */
 int PGTYPEStimestamp_add_interval (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

int
PGTYPEStimestamp_sub_interval(timestamp * tin, interval * span, timestamp * tout)
{
	interval	tspan;

	tspan.month = -span->month;
	tspan.time = -span->time;


	return PGTYPEStimestamp_add_interval(tin, &tspan, tout);
}