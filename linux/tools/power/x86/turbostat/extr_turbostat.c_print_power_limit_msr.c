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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*,unsigned long long,double,char*) ; 
 int /*<<< orphan*/  outf ; 
 unsigned long long rapl_power_units ; 
 double rapl_time_units ; 

void print_power_limit_msr(int cpu, unsigned long long msr, char *label)
{
	fprintf(outf, "cpu%d: %s: %sabled (%f Watts, %f sec, clamp %sabled)\n",
		cpu, label,
		((msr >> 15) & 1) ? "EN" : "DIS",
		((msr >> 0) & 0x7FFF) * rapl_power_units,
		(1.0 + (((msr >> 22) & 0x3)/4.0)) * (1 << ((msr >> 17) & 0x1F)) * rapl_time_units,
		(((msr >> 16) & 1) ? "EN" : "DIS"));

	return;
}