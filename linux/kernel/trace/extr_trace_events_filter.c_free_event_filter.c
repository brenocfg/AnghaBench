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
struct event_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_filter (struct event_filter*) ; 

void free_event_filter(struct event_filter *filter)
{
	__free_filter(filter);
}