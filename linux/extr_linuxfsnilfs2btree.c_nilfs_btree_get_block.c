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
struct nilfs_bmap {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int __nilfs_btree_get_block (struct nilfs_bmap const*,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_btree_get_block(const struct nilfs_bmap *btree, __u64 ptr,
				   struct buffer_head **bhp)
{
	return __nilfs_btree_get_block(btree, ptr, bhp, NULL);
}