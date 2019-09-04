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
struct team_port {scalar_t__ priority; scalar_t__ index; } ;

/* Variables and functions */

__attribute__((used)) static bool team_queue_override_port_has_gt_prio_than(struct team_port *port,
						      struct team_port *cur)
{
	if (port->priority < cur->priority)
		return true;
	if (port->priority > cur->priority)
		return false;
	if (port->index < cur->index)
		return true;
	return false;
}