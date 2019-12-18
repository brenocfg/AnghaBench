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
struct hist_entry {int /*<<< orphan*/  time; } ;
typedef  int /*<<< orphan*/  he_time ;
struct TYPE_2__ {scalar_t__ nanosecs; } ;

/* Variables and functions */
 int repsep_snprintf (char*,size_t,char*,unsigned int,char*) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/  timestamp__scnprintf_nsec (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  timestamp__scnprintf_usec (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int hist_entry__time_snprintf(struct hist_entry *he, char *bf,
				    size_t size, unsigned int width)
{
	char he_time[32];

	if (symbol_conf.nanosecs)
		timestamp__scnprintf_nsec(he->time, he_time,
					  sizeof(he_time));
	else
		timestamp__scnprintf_usec(he->time, he_time,
					  sizeof(he_time));

	return repsep_snprintf(bf, size, "%-.*s", width, he_time);
}