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
struct grub_nilfs2_inode {int dummy; } ;
struct grub_nilfs2_data {int dummy; } ;
struct grub_nilfs2_btree_node {int bn_level; } ;
typedef  int grub_uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int NILFS2_BLOCK_SIZE (struct grub_nilfs2_data*) ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 scalar_t__ grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 unsigned char* grub_malloc (int) ; 
 int grub_nilfs2_btree_get_level (struct grub_nilfs2_btree_node*) ; 
 int /*<<< orphan*/  grub_nilfs2_btree_get_nonroot_node (struct grub_nilfs2_data*,int,unsigned char*) ; 
 struct grub_nilfs2_btree_node* grub_nilfs2_btree_get_root (struct grub_nilfs2_inode*) ; 
 int grub_nilfs2_btree_node_get_ptr (struct grub_nilfs2_data*,struct grub_nilfs2_btree_node*,int) ; 
 int grub_nilfs2_btree_node_lookup (struct grub_nilfs2_btree_node*,int,int*) ; 
 int grub_nilfs2_btree_node_nchildren_max (struct grub_nilfs2_data*,struct grub_nilfs2_btree_node*) ; 
 int grub_nilfs2_dat_translate (struct grub_nilfs2_data*,int) ; 

__attribute__((used)) static grub_uint64_t
grub_nilfs2_btree_lookup (struct grub_nilfs2_data *data,
			  struct grub_nilfs2_inode *inode,
			  grub_uint64_t key, int need_translate)
{
  struct grub_nilfs2_btree_node *node;
#ifndef _MSC_VER
  unsigned char block[NILFS2_BLOCK_SIZE (data)];
#else
  unsigned char * block = grub_malloc(NILFS2_BLOCK_SIZE (data));
#endif
  grub_uint64_t ptr;
  int level, found, index;

  node = grub_nilfs2_btree_get_root (inode);
  level = grub_nilfs2_btree_get_level (node);

  found = grub_nilfs2_btree_node_lookup (node, key, &index);
  ptr = grub_nilfs2_btree_node_get_ptr (data, node, index);
  if (need_translate)
    ptr = grub_nilfs2_dat_translate (data, ptr);

  for (level--; level >= NILFS_BTREE_LEVEL_NODE_MIN; level--)
    {
      grub_nilfs2_btree_get_nonroot_node (data, ptr, block);
      if (grub_errno)
	{
	  return -1;
	}
      node = (struct grub_nilfs2_btree_node *) block;

      if (node->bn_level != level)
	{
	  grub_error (GRUB_ERR_BAD_FS, "btree level mismatch\n");
	  return -1;
	}

      if (!found)
	found = grub_nilfs2_btree_node_lookup (node, key, &index);
      else
	index = 0;

      if (index < grub_nilfs2_btree_node_nchildren_max (data, node))
	{
	  ptr = grub_nilfs2_btree_node_get_ptr (data, node, index);
	  if (need_translate)
	    ptr = grub_nilfs2_dat_translate (data, ptr);
	}
      else
	{
	  grub_error (GRUB_ERR_BAD_FS, "btree corruption\n");
	  return -1;
	}
    }

  if (!found)
    return -1;

  return ptr;
}