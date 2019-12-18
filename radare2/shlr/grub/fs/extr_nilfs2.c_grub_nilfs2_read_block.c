#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct grub_nilfs2_inode {int dummy; } ;
struct grub_nilfs2_data {int dummy; } ;
typedef  scalar_t__ grub_uint64_t ;
typedef  TYPE_1__* grub_fshelp_node_t ;
typedef  int grub_disk_addr_t ;
struct TYPE_3__ {struct grub_nilfs2_inode inode; struct grub_nilfs2_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_FS ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_nilfs2_bmap_lookup (struct grub_nilfs2_data*,struct grub_nilfs2_inode*,int,int) ; 

__attribute__((used)) static grub_disk_addr_t
grub_nilfs2_read_block (grub_fshelp_node_t node, grub_disk_addr_t fileblock)
{
  struct grub_nilfs2_data *data = node->data;
  struct grub_nilfs2_inode *inode = &node->inode;
  grub_uint64_t pptr = -1;

  pptr = grub_nilfs2_bmap_lookup (data, inode, fileblock, 1);
  if (pptr == (grub_uint64_t) - 1)
    {
      grub_error (GRUB_ERR_BAD_FS, "btree lookup failure");
      return -1;
    }

  return pptr;
}