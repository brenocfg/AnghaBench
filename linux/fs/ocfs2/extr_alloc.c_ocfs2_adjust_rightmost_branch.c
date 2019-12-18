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
struct ocfs2_extent_tree {int /*<<< orphan*/  et_ci; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_next_free_rec; struct ocfs2_extent_rec* l_recs; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_adjust_rightmost_records (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,struct ocfs2_path*,struct ocfs2_extent_rec*) ; 
 int ocfs2_extend_trans (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocfs2_find_path (int /*<<< orphan*/ ,struct ocfs2_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_path (struct ocfs2_path*) ; 
 int ocfs2_journal_access_path (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_path*) ; 
 struct ocfs2_path* ocfs2_new_path_from_et (struct ocfs2_extent_tree*) ; 
 struct ocfs2_extent_list* path_leaf_el (struct ocfs2_path*) ; 
 int /*<<< orphan*/  path_num_items (struct ocfs2_path*) ; 

__attribute__((used)) static int ocfs2_adjust_rightmost_branch(handle_t *handle,
					 struct ocfs2_extent_tree *et)
{
	int status;
	struct ocfs2_path *path = NULL;
	struct ocfs2_extent_list *el;
	struct ocfs2_extent_rec *rec;

	path = ocfs2_new_path_from_et(et);
	if (!path) {
		status = -ENOMEM;
		return status;
	}

	status = ocfs2_find_path(et->et_ci, path, UINT_MAX);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	status = ocfs2_extend_trans(handle, path_num_items(path));
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	status = ocfs2_journal_access_path(et->et_ci, handle, path);
	if (status < 0) {
		mlog_errno(status);
		goto out;
	}

	el = path_leaf_el(path);
	rec = &el->l_recs[le16_to_cpu(el->l_next_free_rec) - 1];

	ocfs2_adjust_rightmost_records(handle, et, path, rec);

out:
	ocfs2_free_path(path);
	return status;
}