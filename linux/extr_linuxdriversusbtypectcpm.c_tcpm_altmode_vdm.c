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
struct typec_altmode {int dummy; } ;
struct tcpm_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  vdm_state_machine; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcpm_queue_vdm (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 struct tcpm_port* typec_altmode_get_drvdata (struct typec_altmode*) ; 

__attribute__((used)) static int tcpm_altmode_vdm(struct typec_altmode *altmode,
			    u32 header, const u32 *data, int count)
{
	struct tcpm_port *port = typec_altmode_get_drvdata(altmode);

	mutex_lock(&port->lock);
	tcpm_queue_vdm(port, header, data, count - 1);
	mod_delayed_work(port->wq, &port->vdm_state_machine, 0);
	mutex_unlock(&port->lock);

	return 0;
}