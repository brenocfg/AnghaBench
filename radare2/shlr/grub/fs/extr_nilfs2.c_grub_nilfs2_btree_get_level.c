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
struct grub_nilfs2_btree_node {int bn_level; } ;

/* Variables and functions */

__attribute__((used)) static inline int
grub_nilfs2_btree_get_level (struct grub_nilfs2_btree_node *node)
{
  return node->bn_level;
}