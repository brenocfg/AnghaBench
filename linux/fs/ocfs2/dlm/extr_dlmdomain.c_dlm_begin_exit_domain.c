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
struct TYPE_2__ {int pv_major; int pv_minor; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; TYPE_1__ dlm_locking_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_BEGIN_EXIT_DOMAIN_MSG ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  dlm_send_one_domain_exit (struct dlm_ctxt*,int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_begin_exit_domain(struct dlm_ctxt *dlm)
{
	int node = -1;

	/* Support for begin exit domain was added in 1.2 */
	if (dlm->dlm_locking_proto.pv_major == 1 &&
	    dlm->dlm_locking_proto.pv_minor < 2)
		return;

	/*
	 * Unlike DLM_EXIT_DOMAIN_MSG, DLM_BEGIN_EXIT_DOMAIN_MSG is purely
	 * informational. Meaning if a node does not receive the message,
	 * so be it.
	 */
	spin_lock(&dlm->spinlock);
	while (1) {
		node = find_next_bit(dlm->domain_map, O2NM_MAX_NODES, node + 1);
		if (node >= O2NM_MAX_NODES)
			break;
		if (node == dlm->node_num)
			continue;

		spin_unlock(&dlm->spinlock);
		dlm_send_one_domain_exit(dlm, DLM_BEGIN_EXIT_DOMAIN_MSG, node);
		spin_lock(&dlm->spinlock);
	}
	spin_unlock(&dlm->spinlock);
}