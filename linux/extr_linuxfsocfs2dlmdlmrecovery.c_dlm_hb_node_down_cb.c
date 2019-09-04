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
struct o2nm_node {int dummy; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_hb_node_down (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_fire_domain_eviction_callbacks (struct dlm_ctxt*,int) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

void dlm_hb_node_down_cb(struct o2nm_node *node, int idx, void *data)
{
	struct dlm_ctxt *dlm = data;

	if (!dlm_grab(dlm))
		return;

	/*
	 * This will notify any dlm users that a node in our domain
	 * went away without notifying us first.
	 */
	if (test_bit(idx, dlm->domain_map))
		dlm_fire_domain_eviction_callbacks(dlm, idx);

	spin_lock(&dlm->spinlock);
	__dlm_hb_node_down(dlm, idx);
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);
}