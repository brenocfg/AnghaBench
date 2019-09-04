#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bbc_cpu_temperature {int /*<<< orphan*/  sample_tick; scalar_t__ curr_cpu_temp; void* avg_cpu_temp; scalar_t__ curr_amb_temp; void* avg_amb_temp; } ;
typedef  void* s8 ;

/* Variables and functions */
 int /*<<< orphan*/  analyze_ambient_temp (struct bbc_cpu_temperature*,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analyze_cpu_temp (struct bbc_cpu_temperature*,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void analyze_temps(struct bbc_cpu_temperature *tp, unsigned long *last_warn)
{
	tp->avg_amb_temp = (s8)((int)((int)tp->avg_amb_temp + (int)tp->curr_amb_temp) / 2);
	tp->avg_cpu_temp = (s8)((int)((int)tp->avg_cpu_temp + (int)tp->curr_cpu_temp) / 2);

	analyze_ambient_temp(tp, last_warn, tp->sample_tick);
	analyze_cpu_temp(tp, last_warn, tp->sample_tick);

	tp->sample_tick++;
}