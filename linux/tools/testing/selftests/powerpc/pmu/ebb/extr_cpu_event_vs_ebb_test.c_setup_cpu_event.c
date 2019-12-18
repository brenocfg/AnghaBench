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
struct TYPE_2__ {int exclude_kernel; int exclude_hv; int exclude_idle; } ;
struct event {TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKIP_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_enable (struct event*) ; 
 int /*<<< orphan*/  event_init_named (struct event*,int,char*) ; 
 int /*<<< orphan*/  event_open_with_cpu (struct event*,int) ; 
 int /*<<< orphan*/  require_paranoia_below (int) ; 

__attribute__((used)) static int setup_cpu_event(struct event *event, int cpu)
{
	event_init_named(event, 0x400FA, "PM_RUN_INST_CMPL");

	event->attr.exclude_kernel = 1;
	event->attr.exclude_hv = 1;
	event->attr.exclude_idle = 1;

	SKIP_IF(require_paranoia_below(1));
	FAIL_IF(event_open_with_cpu(event, cpu));
	FAIL_IF(event_enable(event));

	return 0;
}