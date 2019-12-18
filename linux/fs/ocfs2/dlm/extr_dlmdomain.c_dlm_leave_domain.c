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
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_DOMAIN_BACKOFF_MS ; 
 int /*<<< orphan*/  DLM_EXIT_DOMAIN_MSG ; 
 int ENOPROTOOPT ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int dlm_send_one_domain_exit (struct dlm_ctxt*,int /*<<< orphan*/ ,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_leave_domain(struct dlm_ctxt *dlm)
{
	int node, clear_node, status;

	/* At this point we've migrated away all our locks and won't
	 * accept mastership of new ones. The dlm is responsible for
	 * almost nothing now. We make sure not to confuse any joining
	 * nodes and then commence shutdown procedure. */

	spin_lock(&dlm->spinlock);
	/* Clear ourselves from the domain map */
	clear_bit(dlm->node_num, dlm->domain_map);
	while ((node = find_next_bit(dlm->domain_map, O2NM_MAX_NODES,
				     0)) < O2NM_MAX_NODES) {
		/* Drop the dlm spinlock. This is safe wrt the domain_map.
		 * -nodes cannot be added now as the
		 *   query_join_handlers knows to respond with OK_NO_MAP
		 * -we catch the right network errors if a node is
		 *   removed from the map while we're sending him the
		 *   exit message. */
		spin_unlock(&dlm->spinlock);

		clear_node = 1;

		status = dlm_send_one_domain_exit(dlm, DLM_EXIT_DOMAIN_MSG,
						  node);
		if (status < 0 &&
		    status != -ENOPROTOOPT &&
		    status != -ENOTCONN) {
			mlog(ML_NOTICE, "Error %d sending domain exit message "
			     "to node %d\n", status, node);

			/* Not sure what to do here but lets sleep for
			 * a bit in case this was a transient
			 * error... */
			msleep(DLM_DOMAIN_BACKOFF_MS);
			clear_node = 0;
		}

		spin_lock(&dlm->spinlock);
		/* If we're not clearing the node bit then we intend
		 * to loop back around to try again. */
		if (clear_node)
			clear_bit(node, dlm->domain_map);
	}
	spin_unlock(&dlm->spinlock);
}