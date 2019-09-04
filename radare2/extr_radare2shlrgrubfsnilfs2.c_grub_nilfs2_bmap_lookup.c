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
struct grub_nilfs2_btree_node {int bn_flags; } ;
typedef  int /*<<< orphan*/  grub_uint64_t ;

/* Variables and functions */
 int NILFS_BMAP_LARGE ; 
 struct grub_nilfs2_btree_node* grub_nilfs2_btree_get_root (struct grub_nilfs2_inode*) ; 
 int /*<<< orphan*/  grub_nilfs2_btree_lookup (struct grub_nilfs2_data*,struct grub_nilfs2_inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  grub_nilfs2_dat_translate (struct grub_nilfs2_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grub_nilfs2_direct_lookup (struct grub_nilfs2_inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline grub_uint64_t
grub_nilfs2_bmap_lookup (struct grub_nilfs2_data *data,
			 struct grub_nilfs2_inode *inode,
			 grub_uint64_t key, int need_translate)
{
  struct grub_nilfs2_btree_node *root = grub_nilfs2_btree_get_root (inode);
  if (root->bn_flags & NILFS_BMAP_LARGE)
    return grub_nilfs2_btree_lookup (data, inode, key, need_translate);
  else
    {
      grub_uint64_t ptr;
      ptr = grub_nilfs2_direct_lookup (inode, key);
      if (need_translate)
	ptr = grub_nilfs2_dat_translate (data, ptr);
      return ptr;
    }
}