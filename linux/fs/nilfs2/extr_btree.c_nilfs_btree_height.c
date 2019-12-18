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

/* Variables and functions */
 int /*<<< orphan*/  nilfs_btree_get_root (struct nilfs_bmap const*) ; 
 int nilfs_btree_node_get_level (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_btree_height(const struct nilfs_bmap *btree)
{
	return nilfs_btree_node_get_level(nilfs_btree_get_root(btree)) + 1;
}