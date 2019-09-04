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
struct ocfs2_path {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_journal_access; int /*<<< orphan*/  et_root_el; int /*<<< orphan*/  et_root_bh; } ;

/* Variables and functions */
 struct ocfs2_path* ocfs2_new_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ocfs2_path *ocfs2_new_path_from_et(struct ocfs2_extent_tree *et)
{
	return ocfs2_new_path(et->et_root_bh, et->et_root_el,
			      et->et_root_journal_access);
}