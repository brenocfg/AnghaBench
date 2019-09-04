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

/* Variables and functions */
 struct iblock_dev* IBLOCK_DEV (struct se_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 int bdev_physical_block_size (struct block_device*) ; 
 unsigned int ilog2 (int) ; 

__attribute__((used)) static unsigned int iblock_get_lbppbe(struct se_device *dev)
{
	struct iblock_dev *ib_dev = IBLOCK_DEV(dev);
	struct block_device *bd = ib_dev->ibd_bd;
	int logs_per_phys = bdev_physical_block_size(bd) / bdev_logical_block_size(bd);

	return ilog2(logs_per_phys);
}