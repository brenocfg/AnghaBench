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
struct snd_seq_port_subscribe {int dummy; } ;
struct snd_seq_port_subs_info {int count; int (* open ) (int /*<<< orphan*/ ,struct snd_seq_port_subscribe*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  client; } ;
struct snd_seq_client_port {TYPE_1__ addr; int /*<<< orphan*/  owner; int /*<<< orphan*/  private_data; } ;
struct snd_seq_client {scalar_t__ type; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  SNDRV_SEQ_EVENT_PORT_SUBSCRIBED ; 
 scalar_t__ USER_CLIENT ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_seq_client_notify_subscription (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_seq_port_subscribe*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,struct snd_seq_port_subscribe*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subscribe_port(struct snd_seq_client *client,
			  struct snd_seq_client_port *port,
			  struct snd_seq_port_subs_info *grp,
			  struct snd_seq_port_subscribe *info,
			  int send_ack)
{
	int err = 0;

	if (!try_module_get(port->owner))
		return -EFAULT;
	grp->count++;
	if (grp->open && grp->count == 1) {
		err = grp->open(port->private_data, info);
		if (err < 0) {
			module_put(port->owner);
			grp->count--;
		}
	}
	if (err >= 0 && send_ack && client->type == USER_CLIENT)
		snd_seq_client_notify_subscription(port->addr.client, port->addr.port,
						   info, SNDRV_SEQ_EVENT_PORT_SUBSCRIBED);

	return err;
}