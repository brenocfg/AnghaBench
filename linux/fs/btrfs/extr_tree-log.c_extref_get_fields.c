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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_inode_extref {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_inode_extref_index (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 int /*<<< orphan*/  btrfs_inode_extref_name_len (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 int /*<<< orphan*/  btrfs_inode_extref_parent (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int extref_get_fields(struct extent_buffer *eb, unsigned long ref_ptr,
			     u32 *namelen, char **name, u64 *index,
			     u64 *parent_objectid)
{
	struct btrfs_inode_extref *extref;

	extref = (struct btrfs_inode_extref *)ref_ptr;

	*namelen = btrfs_inode_extref_name_len(eb, extref);
	*name = kmalloc(*namelen, GFP_NOFS);
	if (*name == NULL)
		return -ENOMEM;

	read_extent_buffer(eb, *name, (unsigned long)&extref->name,
			   *namelen);

	if (index)
		*index = btrfs_inode_extref_index(eb, extref);
	if (parent_objectid)
		*parent_objectid = btrfs_inode_extref_parent(eb, extref);

	return 0;
}