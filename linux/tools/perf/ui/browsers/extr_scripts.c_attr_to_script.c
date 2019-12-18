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
struct perf_event_attr {int read_format; int sample_type; } ;

/* Variables and functions */
 int PERF_FORMAT_GROUP ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_PHYS_ADDR ; 
 int PERF_SAMPLE_REGS_INTR ; 
 int PERF_SAMPLE_REGS_USER ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

void attr_to_script(char *extra_format, struct perf_event_attr *attr)
{
	extra_format[0] = 0;
	if (attr->read_format & PERF_FORMAT_GROUP)
		strcat(extra_format, " -F +metric");
	if (attr->sample_type & PERF_SAMPLE_BRANCH_STACK)
		strcat(extra_format, " -F +brstackinsn --xed");
	if (attr->sample_type & PERF_SAMPLE_REGS_INTR)
		strcat(extra_format, " -F +iregs");
	if (attr->sample_type & PERF_SAMPLE_REGS_USER)
		strcat(extra_format, " -F +uregs");
	if (attr->sample_type & PERF_SAMPLE_PHYS_ADDR)
		strcat(extra_format, " -F +phys_addr");
}