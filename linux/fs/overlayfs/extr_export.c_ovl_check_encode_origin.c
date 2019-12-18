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
struct ovl_fs {scalar_t__ upper_mnt; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct ovl_fs* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  OVL_INDEX ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int ovl_connect_layer (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_lower (struct dentry*) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ovl_check_encode_origin(struct dentry *dentry)
{
	struct ovl_fs *ofs = dentry->d_sb->s_fs_info;

	/* Upper file handle for pure upper */
	if (!ovl_dentry_lower(dentry))
		return 0;

	/*
	 * Upper file handle for non-indexed upper.
	 *
	 * Root is never indexed, so if there's an upper layer, encode upper for
	 * root.
	 */
	if (ovl_dentry_upper(dentry) &&
	    !ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		return 0;

	/*
	 * Decoding a merge dir, whose origin's ancestor is under a redirected
	 * lower dir or under a non-indexed upper is not always possible.
	 * ovl_connect_layer() will try to make origin's layer "connected" by
	 * copying up a "connectable" ancestor.
	 */
	if (d_is_dir(dentry) && ofs->upper_mnt)
		return ovl_connect_layer(dentry);

	/* Lower file handle for indexed and non-upper dir/non-dir */
	return 1;
}