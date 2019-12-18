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
struct tep_event_filter {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_event_filter*) ; 
 int /*<<< orphan*/  tep_filter_reset (struct tep_event_filter*) ; 
 int /*<<< orphan*/  tep_unref (int /*<<< orphan*/ ) ; 

void tep_filter_free(struct tep_event_filter *filter)
{
	tep_unref(filter->tep);

	tep_filter_reset(filter);

	free(filter);
}