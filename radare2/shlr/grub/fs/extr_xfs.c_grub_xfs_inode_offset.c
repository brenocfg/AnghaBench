#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int log2_inop; int log2_inode; } ;
struct grub_xfs_data {TYPE_1__ sblock; } ;
typedef  int /*<<< orphan*/  grub_uint64_t ;

/* Variables and functions */
 int GRUB_XFS_INO_INOINAG (struct grub_xfs_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
grub_xfs_inode_offset (struct grub_xfs_data *data,
		       grub_uint64_t ino)
{
  int inoag = GRUB_XFS_INO_INOINAG (data, ino);
  return ((inoag & ((1 << data->sblock.log2_inop) - 1)) <<
	  data->sblock.log2_inode);
}