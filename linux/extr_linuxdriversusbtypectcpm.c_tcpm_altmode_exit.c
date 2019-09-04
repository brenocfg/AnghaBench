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
struct typec_altmode {int /*<<< orphan*/  mode; int /*<<< orphan*/  svid; } ;
struct tcpm_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EXIT_MODE ; 
 int /*<<< orphan*/  VDO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VDO_OPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_queue_vdm (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tcpm_port* typec_altmode_get_drvdata (struct typec_altmode*) ; 

__attribute__((used)) static int tcpm_altmode_exit(struct typec_altmode *altmode)
{
	struct tcpm_port *port = typec_altmode_get_drvdata(altmode);
	u32 header;

	mutex_lock(&port->lock);
	header = VDO(altmode->svid, 1, CMD_EXIT_MODE);
	header |= VDO_OPOS(altmode->mode);

	tcpm_queue_vdm(port, header, NULL, 0);
	mod_delayed_work(port->wq, &port->vdm_state_machine, 0);
	mutex_unlock(&port->lock);

	return 0;
}