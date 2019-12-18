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
typedef  int /*<<< orphan*/  uint32_t ;
struct ocfs2_live_connection {int oc_our_slot; int /*<<< orphan*/  oc_wait; int /*<<< orphan*/  oc_this_node; } ;
struct ocfs2_cluster_connection {struct ocfs2_live_connection* cc_private; } ;
struct dlm_slot {int slot; int /*<<< orphan*/  nodeid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_recover_done(void *arg, struct dlm_slot *slots,
		int num_slots, int our_slot,
		uint32_t generation)
{
	struct ocfs2_cluster_connection *conn = arg;
	struct ocfs2_live_connection *lc = conn->cc_private;
	int i;

	for (i = 0; i < num_slots; i++)
		if (slots[i].slot == our_slot) {
			atomic_set(&lc->oc_this_node, slots[i].nodeid);
			break;
		}

	lc->oc_our_slot = our_slot;
	wake_up(&lc->oc_wait);
}