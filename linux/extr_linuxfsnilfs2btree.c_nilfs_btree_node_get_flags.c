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
struct nilfs_btree_node {int bn_flags; } ;

/* Variables and functions */

__attribute__((used)) static int nilfs_btree_node_get_flags(const struct nilfs_btree_node *node)
{
	return node->bn_flags;
}