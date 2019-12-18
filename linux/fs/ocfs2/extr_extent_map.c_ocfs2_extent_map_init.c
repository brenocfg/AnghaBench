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
struct TYPE_2__ {int /*<<< orphan*/  em_list; scalar_t__ em_num_items; } ;
struct ocfs2_inode_info {TYPE_1__ ip_extent_map; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 

void ocfs2_extent_map_init(struct inode *inode)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	oi->ip_extent_map.em_num_items = 0;
	INIT_LIST_HEAD(&oi->ip_extent_map.em_list);
}