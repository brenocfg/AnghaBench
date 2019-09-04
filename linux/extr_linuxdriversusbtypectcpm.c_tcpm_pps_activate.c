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
struct TYPE_2__ {int /*<<< orphan*/  op_curr; int /*<<< orphan*/  out_volt; int /*<<< orphan*/  active; int /*<<< orphan*/  supported; } ;
struct tcpm_port {scalar_t__ state; int pps_status; int pps_pending; int /*<<< orphan*/  swap_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  pps_complete; int /*<<< orphan*/  current_limit; TYPE_1__ pps_data; int /*<<< orphan*/  supply_voltage; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PD_PPS_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  SNK_NEGOTIATE_CAPABILITIES ; 
 int /*<<< orphan*/  SNK_NEGOTIATE_PPS_CAPABILITIES ; 
 scalar_t__ SNK_READY ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcpm_pps_activate(struct tcpm_port *port, bool activate)
{
	int ret = 0;

	mutex_lock(&port->swap_lock);
	mutex_lock(&port->lock);

	if (!port->pps_data.supported) {
		ret = -EOPNOTSUPP;
		goto port_unlock;
	}

	/* Trying to deactivate PPS when already deactivated so just bail */
	if (!port->pps_data.active && !activate)
		goto port_unlock;

	if (port->state != SNK_READY) {
		ret = -EAGAIN;
		goto port_unlock;
	}

	reinit_completion(&port->pps_complete);
	port->pps_status = 0;
	port->pps_pending = true;

	/* Trigger PPS request or move back to standard PDO contract */
	if (activate) {
		port->pps_data.out_volt = port->supply_voltage;
		port->pps_data.op_curr = port->current_limit;
		tcpm_set_state(port, SNK_NEGOTIATE_PPS_CAPABILITIES, 0);
	} else {
		tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
	}
	mutex_unlock(&port->lock);

	if (!wait_for_completion_timeout(&port->pps_complete,
				msecs_to_jiffies(PD_PPS_CTRL_TIMEOUT)))
		ret = -ETIMEDOUT;
	else
		ret = port->pps_status;

	goto swap_unlock;

port_unlock:
	mutex_unlock(&port->lock);
swap_unlock:
	mutex_unlock(&port->swap_lock);

	return ret;
}