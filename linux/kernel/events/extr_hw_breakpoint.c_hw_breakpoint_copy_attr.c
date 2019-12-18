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
struct perf_event_attr {int /*<<< orphan*/  disabled; int /*<<< orphan*/  bp_len; int /*<<< orphan*/  bp_type; int /*<<< orphan*/  bp_addr; } ;

/* Variables and functions */

__attribute__((used)) static void hw_breakpoint_copy_attr(struct perf_event_attr *to,
				    struct perf_event_attr *from)
{
	to->bp_addr = from->bp_addr;
	to->bp_type = from->bp_type;
	to->bp_len  = from->bp_len;
	to->disabled = from->disabled;
}