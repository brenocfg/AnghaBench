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
struct nilfs_btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nilfs_btree_node_dkeys (struct nilfs_btree_node*) ; 

__attribute__((used)) static void
nilfs_btree_node_set_key(struct nilfs_btree_node *node, int index, __u64 key)
{
	*(nilfs_btree_node_dkeys(node) + index) = cpu_to_le64(key);
}