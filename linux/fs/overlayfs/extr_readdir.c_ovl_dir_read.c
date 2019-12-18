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
struct path {int /*<<< orphan*/  dentry; } ;
struct TYPE_2__ {scalar_t__ pos; } ;
struct ovl_readdir_data {int err; scalar_t__ dentry; int /*<<< orphan*/ * first_maybe_whiteout; TYPE_1__ ctx; scalar_t__ count; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int iterate_dir (struct file*,TYPE_1__*) ; 
 int ovl_check_whiteouts (int /*<<< orphan*/ ,struct ovl_readdir_data*) ; 
 struct file* ovl_path_open (struct path*,int) ; 

__attribute__((used)) static inline int ovl_dir_read(struct path *realpath,
			       struct ovl_readdir_data *rdd)
{
	struct file *realfile;
	int err;

	realfile = ovl_path_open(realpath, O_RDONLY | O_DIRECTORY);
	if (IS_ERR(realfile))
		return PTR_ERR(realfile);

	rdd->first_maybe_whiteout = NULL;
	rdd->ctx.pos = 0;
	do {
		rdd->count = 0;
		rdd->err = 0;
		err = iterate_dir(realfile, &rdd->ctx);
		if (err >= 0)
			err = rdd->err;
	} while (!err && rdd->count);

	if (!err && rdd->first_maybe_whiteout && rdd->dentry)
		err = ovl_check_whiteouts(realpath->dentry, rdd);

	fput(realfile);

	return err;
}