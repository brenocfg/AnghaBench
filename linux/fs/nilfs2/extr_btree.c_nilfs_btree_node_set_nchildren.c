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
struct nilfs_btree_node {int /*<<< orphan*/  bn_nchildren; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static void
nilfs_btree_node_set_nchildren(struct nilfs_btree_node *node, int nchildren)
{
	node->bn_nchildren = cpu_to_le16(nchildren);
}