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
struct event_filter {struct event_filter* filter_string; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_prog (struct event_filter*) ; 
 int /*<<< orphan*/  kfree (struct event_filter*) ; 

__attribute__((used)) static void __free_filter(struct event_filter *filter)
{
	if (!filter)
		return;

	free_prog(filter);
	kfree(filter->filter_string);
	kfree(filter);
}