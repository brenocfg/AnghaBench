#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long time_quantum; } ;

/* Variables and functions */
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static long hist_time(unsigned long htime)
{
	unsigned long time_quantum = symbol_conf.time_quantum;
	if (time_quantum)
		return (htime / time_quantum) * time_quantum;
	return htime;
}