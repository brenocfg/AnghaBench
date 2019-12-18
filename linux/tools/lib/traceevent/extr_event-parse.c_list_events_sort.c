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
struct tep_event {int dummy; } ;
typedef  enum tep_event_sort_type { ____Placeholder_tep_event_sort_type } tep_event_sort_type ;

/* Variables and functions */
#define  TEP_EVENT_SORT_ID 130 
#define  TEP_EVENT_SORT_NAME 129 
#define  TEP_EVENT_SORT_SYSTEM 128 
 int events_id_cmp (void const*,void const*) ; 
 int events_name_cmp (void const*,void const*) ; 
 int events_system_cmp (void const*,void const*) ; 
 int /*<<< orphan*/  qsort (struct tep_event**,int,int,int (*) (void const*,void const*)) ; 

__attribute__((used)) static void list_events_sort(struct tep_event **events, int nr_events,
			     enum tep_event_sort_type sort_type)
{
	int (*sort)(const void *a, const void *b);

	switch (sort_type) {
	case TEP_EVENT_SORT_ID:
		sort = events_id_cmp;
		break;
	case TEP_EVENT_SORT_NAME:
		sort = events_name_cmp;
		break;
	case TEP_EVENT_SORT_SYSTEM:
		sort = events_system_cmp;
		break;
	default:
		sort = NULL;
	}

	if (sort)
		qsort(events, nr_events, sizeof(*events), sort);
}