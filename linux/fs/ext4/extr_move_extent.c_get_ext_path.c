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
struct ext4_ext_path {int /*<<< orphan*/ * p_ext; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  EXT4_EX_NOCACHE ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_find_extent (struct inode*,int /*<<< orphan*/ ,struct ext4_ext_path**,int /*<<< orphan*/ ) ; 
 size_t ext_depth (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 

__attribute__((used)) static inline int
get_ext_path(struct inode *inode, ext4_lblk_t lblock,
		struct ext4_ext_path **ppath)
{
	struct ext4_ext_path *path;

	path = ext4_find_extent(inode, lblock, ppath, EXT4_EX_NOCACHE);
	if (IS_ERR(path))
		return PTR_ERR(path);
	if (path[ext_depth(inode)].p_ext == NULL) {
		ext4_ext_drop_refs(path);
		kfree(path);
		*ppath = NULL;
		return -ENODATA;
	}
	*ppath = path;
	return 0;
}