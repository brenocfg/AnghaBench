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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int FILEID_INVALID ; 
 scalar_t__ WARN_ON (int) ; 
 struct dentry* d_find_any_alias (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int ovl_dentry_to_fh (struct dentry*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int ovl_encode_fh(struct inode *inode, u32 *fid, int *max_len,
			 struct inode *parent)
{
	struct dentry *dentry;
	int type;

	/* TODO: encode connectable file handles */
	if (parent)
		return FILEID_INVALID;

	dentry = d_find_any_alias(inode);
	if (WARN_ON(!dentry))
		return FILEID_INVALID;

	type = ovl_dentry_to_fh(dentry, fid, max_len);

	dput(dentry);
	return type;
}