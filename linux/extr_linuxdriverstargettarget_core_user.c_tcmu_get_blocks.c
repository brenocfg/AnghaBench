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
struct tcmu_dev {scalar_t__ dev_size; } ;
struct TYPE_2__ {scalar_t__ block_size; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct tcmu_dev* TCMU_DEV (struct se_device*) ; 
 int /*<<< orphan*/  div_u64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static sector_t tcmu_get_blocks(struct se_device *dev)
{
	struct tcmu_dev *udev = TCMU_DEV(dev);

	return div_u64(udev->dev_size - dev->dev_attrib.block_size,
		       dev->dev_attrib.block_size);
}