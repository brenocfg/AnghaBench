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
struct TYPE_2__ {double period; } ;
struct hist_entry {TYPE_1__ stat; } ;

/* Variables and functions */
 int scnprintf (char*,size_t,char*,double,double) ; 

__attribute__((used)) static int formula_ratio(struct hist_entry *he, struct hist_entry *pair,
			 char *buf, size_t size)
{
	double old_period = he->stat.period;
	double new_period = pair->stat.period;

	return scnprintf(buf, size, "%.0F / %.0F", new_period, old_period);
}