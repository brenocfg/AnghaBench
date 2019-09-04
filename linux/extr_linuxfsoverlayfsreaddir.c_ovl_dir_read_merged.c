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
struct rb_root {int dummy; } ;
struct path {scalar_t__ dentry; } ;
struct TYPE_2__ {int /*<<< orphan*/  actor; } ;
struct ovl_readdir_data {int is_lowest; int is_upper; int /*<<< orphan*/  middle; struct list_head* list; struct rb_root* root; struct dentry* dentry; TYPE_1__ ctx; } ;
struct list_head {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 int ovl_dir_read (struct path*,struct ovl_readdir_data*) ; 
 int /*<<< orphan*/  ovl_fill_merge ; 
 int ovl_path_next (int,struct dentry*,struct path*) ; 

__attribute__((used)) static int ovl_dir_read_merged(struct dentry *dentry, struct list_head *list,
	struct rb_root *root)
{
	int err;
	struct path realpath;
	struct ovl_readdir_data rdd = {
		.ctx.actor = ovl_fill_merge,
		.dentry = dentry,
		.list = list,
		.root = root,
		.is_lowest = false,
	};
	int idx, next;

	for (idx = 0; idx != -1; idx = next) {
		next = ovl_path_next(idx, dentry, &realpath);
		rdd.is_upper = ovl_dentry_upper(dentry) == realpath.dentry;

		if (next != -1) {
			err = ovl_dir_read(&realpath, &rdd);
			if (err)
				break;
		} else {
			/*
			 * Insert lowest layer entries before upper ones, this
			 * allows offsets to be reasonably constant
			 */
			list_add(&rdd.middle, rdd.list);
			rdd.is_lowest = true;
			err = ovl_dir_read(&realpath, &rdd);
			list_del(&rdd.middle);
		}
	}
	return err;
}