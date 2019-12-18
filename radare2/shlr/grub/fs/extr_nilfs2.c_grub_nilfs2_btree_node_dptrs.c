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
struct grub_nilfs2_data {int dummy; } ;
struct grub_nilfs2_btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  grub_uint64_t ;

/* Variables and functions */
 scalar_t__ grub_nilfs2_btree_node_dkeys (struct grub_nilfs2_btree_node*) ; 
 scalar_t__ grub_nilfs2_btree_node_nchildren_max (struct grub_nilfs2_data*,struct grub_nilfs2_btree_node*) ; 

__attribute__((used)) static inline grub_uint64_t *
grub_nilfs2_btree_node_dptrs (struct grub_nilfs2_data *data,
			      struct grub_nilfs2_btree_node *node)
{
  return (grub_uint64_t *) (grub_nilfs2_btree_node_dkeys (node) +
			    grub_nilfs2_btree_node_nchildren_max (data,
								  node));
}