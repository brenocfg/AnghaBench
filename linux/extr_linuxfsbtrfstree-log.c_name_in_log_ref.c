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
struct btrfs_root {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_EXTREF_KEY ; 
 int /*<<< orphan*/  BTRFS_INODE_REF_KEY ; 
 scalar_t__ backref_in_log (struct btrfs_root*,struct btrfs_key*,int /*<<< orphan*/  const,char const*,int const) ; 
 int /*<<< orphan*/  btrfs_extref_hash (int /*<<< orphan*/  const,char const*,int const) ; 

__attribute__((used)) static bool name_in_log_ref(struct btrfs_root *log_root,
			    const char *name, const int name_len,
			    const u64 dirid, const u64 ino)
{
	struct btrfs_key search_key;

	search_key.objectid = ino;
	search_key.type = BTRFS_INODE_REF_KEY;
	search_key.offset = dirid;
	if (backref_in_log(log_root, &search_key, dirid, name, name_len))
		return true;

	search_key.type = BTRFS_INODE_EXTREF_KEY;
	search_key.offset = btrfs_extref_hash(dirid, name, name_len);
	if (backref_in_log(log_root, &search_key, dirid, name, name_len))
		return true;

	return false;
}