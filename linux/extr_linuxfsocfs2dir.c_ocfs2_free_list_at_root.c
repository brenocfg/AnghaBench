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
struct ocfs2_dir_lookup_result {int /*<<< orphan*/ * dl_prev_leaf_bh; } ;

/* Variables and functions */

__attribute__((used)) static int ocfs2_free_list_at_root(struct ocfs2_dir_lookup_result *res)
{
	return res->dl_prev_leaf_bh == NULL;
}