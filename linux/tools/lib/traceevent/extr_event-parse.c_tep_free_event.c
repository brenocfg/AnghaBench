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
struct TYPE_2__ {int /*<<< orphan*/  args; struct tep_event* format; } ;
struct tep_event {TYPE_1__ print_fmt; int /*<<< orphan*/  format; struct tep_event* system; struct tep_event* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct tep_event*) ; 
 int /*<<< orphan*/  free_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_formats (int /*<<< orphan*/ *) ; 

void tep_free_event(struct tep_event *event)
{
	free(event->name);
	free(event->system);

	free_formats(&event->format);

	free(event->print_fmt.format);
	free_args(event->print_fmt.args);

	free(event);
}