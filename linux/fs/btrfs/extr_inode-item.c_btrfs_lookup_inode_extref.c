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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_inode_extref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_EXTREF_KEY ; 
 struct btrfs_inode_extref* ERR_PTR (int) ; 
 int /*<<< orphan*/  btrfs_extref_hash (int /*<<< orphan*/ ,char const*,int) ; 
 struct btrfs_inode_extref* btrfs_find_name_in_ext_backref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 

struct btrfs_inode_extref *
btrfs_lookup_inode_extref(struct btrfs_trans_handle *trans,
			  struct btrfs_root *root,
			  struct btrfs_path *path,
			  const char *name, int name_len,
			  u64 inode_objectid, u64 ref_objectid, int ins_len,
			  int cow)
{
	int ret;
	struct btrfs_key key;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = btrfs_extref_hash(ref_objectid, name, name_len);

	ret = btrfs_search_slot(trans, root, &key, path, ins_len, cow);
	if (ret < 0)
		return ERR_PTR(ret);
	if (ret > 0)
		return NULL;
	return btrfs_find_name_in_ext_backref(path->nodes[0], path->slots[0],
					      ref_objectid, name, name_len);

}