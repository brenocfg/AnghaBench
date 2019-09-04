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
struct ocfs2_super {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_init_inode_steal_slot (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_init_meta_steal_slot (struct ocfs2_super*) ; 

void ocfs2_init_steal_slots(struct ocfs2_super *osb)
{
	ocfs2_init_inode_steal_slot(osb);
	ocfs2_init_meta_steal_slot(osb);
}