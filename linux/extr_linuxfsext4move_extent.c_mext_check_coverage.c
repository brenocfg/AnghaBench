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
struct inode {int dummy; } ;
struct ext4_extent {int dummy; } ;
struct ext4_ext_path {struct ext4_extent* p_ext; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 scalar_t__ ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_is_unwritten (struct ext4_extent*) ; 
 size_t ext_depth (struct inode*) ; 
 int get_ext_path (struct inode*,scalar_t__,struct ext4_ext_path**) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 

__attribute__((used)) static int
mext_check_coverage(struct inode *inode, ext4_lblk_t from, ext4_lblk_t count,
		    int unwritten, int *err)
{
	struct ext4_ext_path *path = NULL;
	struct ext4_extent *ext;
	int ret = 0;
	ext4_lblk_t last = from + count;
	while (from < last) {
		*err = get_ext_path(inode, from, &path);
		if (*err)
			goto out;
		ext = path[ext_depth(inode)].p_ext;
		if (unwritten != ext4_ext_is_unwritten(ext))
			goto out;
		from += ext4_ext_get_actual_len(ext);
		ext4_ext_drop_refs(path);
	}
	ret = 1;
out:
	ext4_ext_drop_refs(path);
	kfree(path);
	return ret;
}