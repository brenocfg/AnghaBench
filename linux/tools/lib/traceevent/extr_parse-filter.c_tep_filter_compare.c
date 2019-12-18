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
struct tep_filter_type {TYPE_1__* filter; int /*<<< orphan*/  event_id; } ;
struct tep_event_filter {int filters; struct tep_filter_type* event_filters; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 char* arg_to_str (struct tep_event_filter*,TYPE_1__*) ; 
 struct tep_filter_type* find_filter_type (struct tep_event_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int tep_filter_compare(struct tep_event_filter *filter1, struct tep_event_filter *filter2)
{
	struct tep_filter_type *filter_type1;
	struct tep_filter_type *filter_type2;
	char *str1, *str2;
	int result;
	int i;

	/* Do the easy checks first */
	if (filter1->filters != filter2->filters)
		return 0;
	if (!filter1->filters && !filter2->filters)
		return 1;

	/*
	 * Now take a look at each of the events to see if they have the same
	 * filters to them.
	 */
	for (i = 0; i < filter1->filters; i++) {
		filter_type1 = &filter1->event_filters[i];
		filter_type2 = find_filter_type(filter2, filter_type1->event_id);
		if (!filter_type2)
			break;
		if (filter_type1->filter->type != filter_type2->filter->type)
			break;
		/* The best way to compare complex filters is with strings */
		str1 = arg_to_str(filter1, filter_type1->filter);
		str2 = arg_to_str(filter2, filter_type2->filter);
		if (str1 && str2)
			result = strcmp(str1, str2) != 0;
		else
			/* bail out if allocation fails */
			result = 1;

		free(str1);
		free(str2);
		if (result)
			break;
	}

	if (i < filter1->filters)
		return 0;
	return 1;
}