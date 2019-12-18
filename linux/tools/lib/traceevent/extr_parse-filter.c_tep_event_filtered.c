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
struct tep_filter_type {int dummy; } ;
struct tep_event_filter {int /*<<< orphan*/  filters; } ;

/* Variables and functions */
 struct tep_filter_type* find_filter_type (struct tep_event_filter*,int) ; 

int tep_event_filtered(struct tep_event_filter *filter, int event_id)
{
	struct tep_filter_type *filter_type;

	if (!filter->filters)
		return 0;

	filter_type = find_filter_type(filter, event_id);

	return filter_type ? 1 : 0;
}