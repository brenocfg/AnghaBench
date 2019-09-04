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
struct timer_list {int dummy; } ;
struct fcoe_port {int /*<<< orphan*/  lport; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcoe_check_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fcoe_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct fcoe_port* port ; 
 int /*<<< orphan*/  timer ; 

void fcoe_queue_timer(struct timer_list *t)
{
	struct fcoe_port *port = from_timer(port, t, timer);

	fcoe_check_wait_queue(port->lport, NULL);
}