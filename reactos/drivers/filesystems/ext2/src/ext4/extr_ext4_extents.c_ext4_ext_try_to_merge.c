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
struct ext4_extent_header {int dummy; } ;
struct ext4_extent {int dummy; } ;
struct ext4_ext_path {struct ext4_extent_header* p_hdr; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct ext4_extent* EXT_FIRST_EXTENT (struct ext4_extent_header*) ; 
 int ext4_ext_try_to_merge_right (struct inode*,struct ext4_ext_path*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_try_to_merge_up (void*,int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*) ; 
 unsigned int ext_depth (struct inode*) ; 

__attribute__((used)) static void ext4_ext_try_to_merge(void *icb, handle_t *handle,
		struct inode *inode,
		struct ext4_ext_path *path,
		struct ext4_extent *ex) {
	struct ext4_extent_header *eh;
	unsigned int depth;
	int merge_done = 0;

	depth = ext_depth(inode);
	BUG_ON(path[depth].p_hdr == NULL);
	eh = path[depth].p_hdr;

	if (ex > EXT_FIRST_EXTENT(eh))
		merge_done = ext4_ext_try_to_merge_right(inode, path, ex - 1);

	if (!merge_done)
		(void) ext4_ext_try_to_merge_right(inode, path, ex);

	ext4_ext_try_to_merge_up(icb, handle, inode, path);
}