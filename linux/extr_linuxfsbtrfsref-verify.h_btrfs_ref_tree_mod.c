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

/* Variables and functions */

__attribute__((used)) static inline int btrfs_ref_tree_mod(struct btrfs_root *root, u64 bytenr,
				     u64 num_bytes, u64 parent, u64 ref_root,
				     u64 owner, u64 offset, int action)
{
	return 0;
}