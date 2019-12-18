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
struct o2net_msg {scalar_t__ buf; } ;
struct dlm_ctxt {scalar_t__ joining_node; int /*<<< orphan*/  spinlock; } ;
struct dlm_cancel_join {scalar_t__ node_idx; int /*<<< orphan*/  name_len; int /*<<< orphan*/  domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 struct dlm_ctxt* __dlm_lookup_domain_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dlm_set_joining_node (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_cancel_join_handler(struct o2net_msg *msg, u32 len, void *data,
				   void **ret_data)
{
	struct dlm_cancel_join *cancel;
	struct dlm_ctxt *dlm = NULL;

	cancel = (struct dlm_cancel_join *) msg->buf;

	mlog(0, "node %u cancels join on domain %s\n", cancel->node_idx,
		  cancel->domain);

	spin_lock(&dlm_domain_lock);
	dlm = __dlm_lookup_domain_full(cancel->domain, cancel->name_len);

	if (dlm) {
		spin_lock(&dlm->spinlock);

		/* Yikes, this guy wants to cancel his join. No
		 * problem, we simply cleanup our join state. */
		BUG_ON(dlm->joining_node != cancel->node_idx);
		__dlm_set_joining_node(dlm, DLM_LOCK_RES_OWNER_UNKNOWN);

		spin_unlock(&dlm->spinlock);
	}
	spin_unlock(&dlm_domain_lock);

	return 0;
}