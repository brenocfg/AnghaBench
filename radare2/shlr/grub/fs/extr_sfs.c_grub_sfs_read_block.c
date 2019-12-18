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
typedef  TYPE_1__* grub_fshelp_node_t ;
typedef  scalar_t__ grub_err_t ;
typedef  int grub_disk_addr_t ;
struct TYPE_3__ {int block; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_FILE_READ_ERROR ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ grub_sfs_read_extent (int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static grub_disk_addr_t
grub_sfs_read_block (grub_fshelp_node_t node, grub_disk_addr_t fileblock)
{
  int blk = node->block;
  int size = 0;
  int next = 0;

  while (blk)
    {
      grub_err_t err;

      /* In case of the first block we don't have to lookup the
	 extent, the minimum size is always 1.  */
      if (fileblock == 0)
	return blk;

      err = grub_sfs_read_extent (node->data, blk, &size, &next);
      if (err)
	return 0;

      if (fileblock < (unsigned int) size)
	return fileblock + blk;

      fileblock -= size;

      blk = next;
    }

  grub_error (GRUB_ERR_FILE_READ_ERROR,
	      "reading a SFS block outside the extent");

  return 0;
}