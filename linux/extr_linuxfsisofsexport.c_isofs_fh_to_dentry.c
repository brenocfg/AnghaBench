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
struct super_block {int dummy; } ;
struct isofs_fid {int /*<<< orphan*/  generation; int /*<<< orphan*/  offset; int /*<<< orphan*/  block; } ;
struct fid {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* isofs_export_iget (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *isofs_fh_to_dentry(struct super_block *sb,
	struct fid *fid, int fh_len, int fh_type)
{
	struct isofs_fid *ifid = (struct isofs_fid *)fid;

	if (fh_len < 3 || fh_type > 2)
		return NULL;

	return isofs_export_iget(sb, ifid->block, ifid->offset,
			ifid->generation);
}