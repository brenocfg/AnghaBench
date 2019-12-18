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
struct grub_hfsplus_key {int dummy; } ;
struct grub_hfsplus_btree {int dummy; } ;
struct grub_hfsplus_btnode {int dummy; } ;

/* Variables and functions */
 unsigned int grub_hfsplus_btree_recoffset (struct grub_hfsplus_btree*,struct grub_hfsplus_btnode*,int) ; 

__attribute__((used)) static inline struct grub_hfsplus_key *
grub_hfsplus_btree_recptr (struct grub_hfsplus_btree *btree,
			   struct grub_hfsplus_btnode *node, int index)
{
  char *cnode = (char *) node;
  unsigned int offset;
  offset = grub_hfsplus_btree_recoffset (btree, node, index);
  return (struct grub_hfsplus_key *) &cnode[offset];
}