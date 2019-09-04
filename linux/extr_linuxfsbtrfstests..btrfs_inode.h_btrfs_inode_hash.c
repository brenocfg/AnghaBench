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
typedef  int u64 ;
struct btrfs_root {int objectid; } ;

/* Variables and functions */
 int GOLDEN_RATIO_PRIME ; 

__attribute__((used)) static inline unsigned long btrfs_inode_hash(u64 objectid,
					     const struct btrfs_root *root)
{
	u64 h = objectid ^ (root->objectid * GOLDEN_RATIO_PRIME);

#if BITS_PER_LONG == 32
	h = (h >> 32) ^ (h & 0xffffffff);
#endif

	return (unsigned long)h;
}