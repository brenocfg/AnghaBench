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
struct tcpm_port {int swap_pending; int swap_status; int non_pd_role_swap; int /*<<< orphan*/  swap_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcpm_swap_complete(struct tcpm_port *port, int result)
{
	if (port->swap_pending) {
		port->swap_status = result;
		port->swap_pending = false;
		port->non_pd_role_swap = false;
		complete(&port->swap_complete);
	}
}