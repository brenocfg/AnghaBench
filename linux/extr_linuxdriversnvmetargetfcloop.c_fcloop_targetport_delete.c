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
struct nvmet_fc_target_port {struct fcloop_tport* private; } ;
struct fcloop_tport {int /*<<< orphan*/  nport; } ;

/* Variables and functions */
 int /*<<< orphan*/  fcloop_nport_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fcloop_targetport_delete(struct nvmet_fc_target_port *targetport)
{
	struct fcloop_tport *tport = targetport->private;

	fcloop_nport_put(tport->nport);
}