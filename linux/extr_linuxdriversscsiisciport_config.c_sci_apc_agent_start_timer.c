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
typedef  int /*<<< orphan*/  u32 ;
struct sci_port_configuration_agent {int timer_pending; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  sci_mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sci_apc_agent_start_timer(struct sci_port_configuration_agent *port_agent,
				      u32 timeout)
{
	port_agent->timer_pending = true;
	sci_mod_timer(&port_agent->timer, timeout);
}