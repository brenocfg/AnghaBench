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
struct grub_nilfs2_inode {int /*<<< orphan*/ * i_bmap; } ;
struct grub_nilfs2_btree_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct grub_nilfs2_btree_node *
grub_nilfs2_btree_get_root (struct grub_nilfs2_inode *inode)
{
  return (struct grub_nilfs2_btree_node *) &inode->i_bmap[0];
}