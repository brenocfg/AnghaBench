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
struct dentry {int dummy; } ;
struct TYPE_2__ {int i_nlink; } ;

/* Variables and functions */
 TYPE_1__* d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 struct dentry* ovl_dentry_lower (struct dentry*) ; 

__attribute__((used)) static bool ovl_need_absolute_redirect(struct dentry *dentry, bool samedir)
{
	struct dentry *lowerdentry;

	if (!samedir)
		return true;

	if (d_is_dir(dentry))
		return false;

	/*
	 * For non-dir hardlinked files, we need absolute redirects
	 * in general as two upper hardlinks could be in different
	 * dirs. We could put a relative redirect now and convert
	 * it to absolute redirect later. But when nlink > 1 and
	 * indexing is on, that means relative redirect needs to be
	 * converted to absolute during copy up of another lower
	 * hardllink as well.
	 *
	 * So without optimizing too much, just check if lower is
	 * a hard link or not. If lower is hard link, put absolute
	 * redirect.
	 */
	lowerdentry = ovl_dentry_lower(dentry);
	return (d_inode(lowerdentry)->i_nlink > 1);
}