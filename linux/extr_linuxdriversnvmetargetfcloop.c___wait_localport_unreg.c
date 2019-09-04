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
struct fcloop_lport {int /*<<< orphan*/  unreg_done; int /*<<< orphan*/  localport; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fcloop_lport*) ; 
 int nvme_fc_unregister_localport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__wait_localport_unreg(struct fcloop_lport *lport)
{
	int ret;

	init_completion(&lport->unreg_done);

	ret = nvme_fc_unregister_localport(lport->localport);

	wait_for_completion(&lport->unreg_done);

	kfree(lport);

	return ret;
}