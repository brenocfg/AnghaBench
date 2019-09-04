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
struct gfs2_sbd {struct dentry* debugfs_dentry_sbstats; struct dentry* debugfs_dir; struct dentry* debugfs_dentry_glstats; struct dentry* debugfs_dentry_glocks; int /*<<< orphan*/  sd_table_name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFREG ; 
 int S_IRUGO ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_delete_debugfs_file (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_glocks_fops ; 
 int /*<<< orphan*/  gfs2_glstats_fops ; 
 int /*<<< orphan*/  gfs2_root ; 
 int /*<<< orphan*/  gfs2_sbstats_fops ; 

int gfs2_create_debugfs_file(struct gfs2_sbd *sdp)
{
	struct dentry *dent;

	dent = debugfs_create_dir(sdp->sd_table_name, gfs2_root);
	if (IS_ERR_OR_NULL(dent))
		goto fail;
	sdp->debugfs_dir = dent;

	dent = debugfs_create_file("glocks",
				   S_IFREG | S_IRUGO,
				   sdp->debugfs_dir, sdp,
				   &gfs2_glocks_fops);
	if (IS_ERR_OR_NULL(dent))
		goto fail;
	sdp->debugfs_dentry_glocks = dent;

	dent = debugfs_create_file("glstats",
				   S_IFREG | S_IRUGO,
				   sdp->debugfs_dir, sdp,
				   &gfs2_glstats_fops);
	if (IS_ERR_OR_NULL(dent))
		goto fail;
	sdp->debugfs_dentry_glstats = dent;

	dent = debugfs_create_file("sbstats",
				   S_IFREG | S_IRUGO,
				   sdp->debugfs_dir, sdp,
				   &gfs2_sbstats_fops);
	if (IS_ERR_OR_NULL(dent))
		goto fail;
	sdp->debugfs_dentry_sbstats = dent;

	return 0;
fail:
	gfs2_delete_debugfs_file(sdp);
	return dent ? PTR_ERR(dent) : -ENOMEM;
}