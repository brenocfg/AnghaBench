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
struct TYPE_2__ {int pinned; int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_enable (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_open_with_pid (struct event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_child_event(struct event *event, pid_t child_pid)
{
	event_init_named(event, 0x400FA, "PM_RUN_INST_CMPL");

	event->attr.pinned = 1;

	event->attr.exclude_kernel = 1;
	event->attr.exclude_hv = 1;
	event->attr.exclude_idle = 1;

	FAIL_IF(event_open_with_pid(event, child_pid));
	FAIL_IF(event_enable(event));

	return 0;
}