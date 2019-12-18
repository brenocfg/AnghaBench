#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_path {int p_tree_depth; } ;
struct TYPE_4__ {int h_buffer_credits; } ;
typedef  TYPE_1__ handle_t ;

/* Variables and functions */
 int ocfs2_extend_trans (TYPE_1__*,int) ; 

__attribute__((used)) static int ocfs2_extend_rotate_transaction(handle_t *handle, int subtree_depth,
					   int op_credits,
					   struct ocfs2_path *path)
{
	int ret = 0;
	int credits = (path->p_tree_depth - subtree_depth) * 2 + 1 + op_credits;

	if (handle->h_buffer_credits < credits)
		ret = ocfs2_extend_trans(handle,
					 credits - handle->h_buffer_credits);

	return ret;
}