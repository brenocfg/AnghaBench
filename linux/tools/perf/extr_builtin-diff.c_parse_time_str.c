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
struct data__file {int dummy; } ;
struct TYPE_2__ {scalar_t__ time_str; } ;

/* Variables and functions */
 int parse_absolute_time (struct data__file*,char**) ; 
 int parse_percent_time (struct data__file*) ; 
 TYPE_1__ pdiff ; 

__attribute__((used)) static int parse_time_str(struct data__file *d, char *abstime_ostr,
			   char **pabstime_tmp)
{
	int ret = 0;

	if (abstime_ostr)
		ret = parse_absolute_time(d, pabstime_tmp);
	else if (pdiff.time_str)
		ret = parse_percent_time(d);

	return ret;
}