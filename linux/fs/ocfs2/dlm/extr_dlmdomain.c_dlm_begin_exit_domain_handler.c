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
struct dlm_exit_domain {unsigned int node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  exit_domain_map; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_begin_exit_domain_handler(struct o2net_msg *msg, u32 len,
					 void *data, void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	unsigned int node;
	struct dlm_exit_domain *exit_msg = (struct dlm_exit_domain *) msg->buf;

	if (!dlm_grab(dlm))
		return 0;

	node = exit_msg->node_idx;
	mlog(0, "%s: Node %u sent a begin exit domain message\n", dlm->name, node);

	spin_lock(&dlm->spinlock);
	set_bit(node, dlm->exit_domain_map);
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);

	return 0;
}