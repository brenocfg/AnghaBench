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
struct dlm_master_list_entry {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  node_map; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_mle_node_down(struct dlm_ctxt *dlm,
			      struct dlm_master_list_entry *mle,
			      struct o2nm_node *node, int idx)
{
	spin_lock(&mle->spinlock);

	if (!test_bit(idx, mle->node_map))
		mlog(0, "node %u already removed from nodemap!\n", idx);
	else
		clear_bit(idx, mle->node_map);

	spin_unlock(&mle->spinlock);
}