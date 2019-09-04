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
struct nvme_fc_local_port {struct fcloop_lport_priv* private; } ;
struct fcloop_lport_priv {struct fcloop_lport* lport; } ;
struct fcloop_lport {int /*<<< orphan*/  unreg_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fcloop_localport_delete(struct nvme_fc_local_port *localport)
{
	struct fcloop_lport_priv *lport_priv = localport->private;
	struct fcloop_lport *lport = lport_priv->lport;

	/* release any threads waiting for the unreg to complete */
	complete(&lport->unreg_done);
}