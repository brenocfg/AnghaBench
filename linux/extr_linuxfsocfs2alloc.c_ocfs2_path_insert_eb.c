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
struct ocfs2_path {TYPE_1__* p_node; } ;
struct ocfs2_extent_block {int /*<<< orphan*/  h_list; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * el; struct buffer_head* bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 

__attribute__((used)) static inline void ocfs2_path_insert_eb(struct ocfs2_path *path, int index,
					struct buffer_head *eb_bh)
{
	struct ocfs2_extent_block *eb = (struct ocfs2_extent_block *)eb_bh->b_data;

	/*
	 * Right now, no root bh is an extent block, so this helps
	 * catch code errors with dinode trees. The assertion can be
	 * safely removed if we ever need to insert extent block
	 * structures at the root.
	 */
	BUG_ON(index == 0);

	path->p_node[index].bh = eb_bh;
	path->p_node[index].el = &eb->h_list;
}