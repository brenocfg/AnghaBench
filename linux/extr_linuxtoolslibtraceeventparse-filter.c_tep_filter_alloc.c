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
struct tep_handle {int dummy; } ;
struct event_filter {struct tep_handle* pevent; } ;

/* Variables and functions */
 struct event_filter* malloc (int) ; 
 int /*<<< orphan*/  memset (struct event_filter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tep_ref (struct tep_handle*) ; 

struct event_filter *tep_filter_alloc(struct tep_handle *pevent)
{
	struct event_filter *filter;

	filter = malloc(sizeof(*filter));
	if (filter == NULL)
		return NULL;

	memset(filter, 0, sizeof(*filter));
	filter->pevent = pevent;
	tep_ref(pevent);

	return filter;
}