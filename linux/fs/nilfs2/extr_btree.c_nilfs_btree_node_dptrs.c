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
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 scalar_t__ nilfs_btree_node_dkeys (struct nilfs_btree_node const*) ; 

__attribute__((used)) static __le64 *
nilfs_btree_node_dptrs(const struct nilfs_btree_node *node, int ncmax)
{
	return (__le64 *)(nilfs_btree_node_dkeys(node) + ncmax);
}