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
struct grub_nilfs2_btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  grub_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_le_to_cpu64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * grub_nilfs2_btree_node_dkeys (struct grub_nilfs2_btree_node*) ; 

__attribute__((used)) static inline grub_uint64_t
grub_nilfs2_btree_node_get_key (struct grub_nilfs2_btree_node *node,
				int index)
{
  return grub_le_to_cpu64 (*(grub_nilfs2_btree_node_dkeys (node) + index));
}