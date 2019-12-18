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
struct ocfs2_super {int /*<<< orphan*/  osb_recovering_orphan_dirs; int /*<<< orphan*/  node_map_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_node_map_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ocfs2_init_node_maps(struct ocfs2_super *osb)
{
	spin_lock_init(&osb->node_map_lock);
	ocfs2_node_map_init(&osb->osb_recovering_orphan_dirs);
}