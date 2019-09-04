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
struct btrfs_path {scalar_t__* slots; int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 scalar_t__ btrfs_header_nritems (int /*<<< orphan*/ ) ; 
 int btrfs_next_old_leaf (struct btrfs_root*,struct btrfs_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int btrfs_next_old_item(struct btrfs_root *root,
				      struct btrfs_path *p, u64 time_seq)
{
	++p->slots[0];
	if (p->slots[0] >= btrfs_header_nritems(p->nodes[0]))
		return btrfs_next_old_leaf(root, p, time_seq);
	return 0;
}