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
struct btrfs_delayed_extent_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_delayed_extent_op_cachep ; 
 struct btrfs_delayed_extent_op* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct btrfs_delayed_extent_op *
btrfs_alloc_delayed_extent_op(void)
{
	return kmem_cache_alloc(btrfs_delayed_extent_op_cachep, GFP_NOFS);
}