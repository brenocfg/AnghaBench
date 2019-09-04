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
struct se_device {int dummy; } ;
struct iblock_dev {struct block_device* ibd_bd; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;

/* Variables and functions */
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 int bdev_alignment_offset (struct block_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 

__attribute__((used)) static sector_t iblock_get_alignment_offset_lbas(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	struct block_device *bd = ib_dev->ibd_bd;
	int ret;

	ret = bdev_alignment_offset(bd);
	if (ret == -1)
		return 0;

	/* convert offset-bytes to offset-lbas */
	return ret / bdev_logical_block_size(bd);
}