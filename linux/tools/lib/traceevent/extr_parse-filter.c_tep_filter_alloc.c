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
struct tep_event_filter {struct tep_handle* tep; } ;

/* Variables and functions */
 struct tep_event_filter* malloc (int) ; 
 int /*<<< orphan*/  memset (struct tep_event_filter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tep_ref (struct tep_handle*) ; 

struct tep_event_filter *tep_filter_alloc(struct tep_handle *tep)
{
	struct tep_event_filter *filter;

	filter = malloc(sizeof(*filter));
	if (filter == NULL)
		return NULL;

	memset(filter, 0, sizeof(*filter));
	filter->tep = tep;
	tep_ref(tep);

	return filter;
}