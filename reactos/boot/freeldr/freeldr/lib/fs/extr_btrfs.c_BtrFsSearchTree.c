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
struct btrfs_root_item {int /*<<< orphan*/  level; int /*<<< orphan*/  bytenr; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  _BtrFsSearchTree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_disk_key*,struct btrfs_path*) ; 

__attribute__((used)) static inline BOOLEAN
BtrFsSearchTree(const struct btrfs_root_item *root, struct btrfs_disk_key *key, struct btrfs_path *path)
{
    return _BtrFsSearchTree(root->bytenr, root->level, key, path);
}