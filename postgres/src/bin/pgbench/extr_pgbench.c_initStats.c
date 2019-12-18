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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {int /*<<< orphan*/  lag; int /*<<< orphan*/  latency; scalar_t__ skipped; scalar_t__ cnt; int /*<<< orphan*/  start_time; } ;
typedef  TYPE_1__ StatsData ;

/* Variables and functions */
 int /*<<< orphan*/  initSimpleStats (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
initStats(StatsData *sd, time_t start_time)
{
	sd->start_time = start_time;
	sd->cnt = 0;
	sd->skipped = 0;
	initSimpleStats(&sd->latency);
	initSimpleStats(&sd->lag);
}