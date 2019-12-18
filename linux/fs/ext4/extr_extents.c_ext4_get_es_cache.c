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
struct inode {int dummy; } ;
struct fiemap_extent_info {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 TYPE_1__* EXT4_I (struct inode*) ; 
 int _ext4_fiemap (struct inode*,struct fiemap_extent_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_fill_es_cache_info ; 
 int ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int ext4_get_es_cache(struct inode *inode, struct fiemap_extent_info *fieinfo,
		      __u64 start, __u64 len)
{
	if (ext4_has_inline_data(inode)) {
		int has_inline;

		down_read(&EXT4_I(inode)->xattr_sem);
		has_inline = ext4_has_inline_data(inode);
		up_read(&EXT4_I(inode)->xattr_sem);
		if (has_inline)
			return 0;
	}

	return _ext4_fiemap(inode, fieinfo, start, len,
			    ext4_fill_es_cache_info);
}