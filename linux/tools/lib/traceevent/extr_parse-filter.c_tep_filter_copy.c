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
struct tep_event_filter {int filters; int /*<<< orphan*/ * event_filters; } ;

/* Variables and functions */
 scalar_t__ copy_filter_type (struct tep_event_filter*,struct tep_event_filter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tep_filter_reset (struct tep_event_filter*) ; 

int tep_filter_copy(struct tep_event_filter *dest, struct tep_event_filter *source)
{
	int ret = 0;
	int i;

	tep_filter_reset(dest);

	for (i = 0; i < source->filters; i++) {
		if (copy_filter_type(dest, source, &source->event_filters[i]))
			ret = -1;
	}
	return ret;
}