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
typedef  void* u32 ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct knav_link_ram_block {int size; int /*<<< orphan*/ * virt; scalar_t__ dma; } ;
struct knav_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * dmam_alloc_coherent (int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32_array (struct device_node*,char const*,void**,int) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int knav_get_link_ram(struct knav_device *kdev,
				       const char *name,
				       struct knav_link_ram_block *block)
{
	struct platform_device *pdev = to_platform_device(kdev->dev);
	struct device_node *node = pdev->dev.of_node;
	u32 temp[2];

	/*
	 * Note: link ram resources are specified in "entry" sized units. In
	 * reality, although entries are ~40bits in hardware, we treat them as
	 * 64-bit entities here.
	 *
	 * For example, to specify the internal link ram for Keystone-I class
	 * devices, we would set the linkram0 resource to 0x80000-0x83fff.
	 *
	 * This gets a bit weird when other link rams are used.  For example,
	 * if the range specified is 0x0c000000-0x0c003fff (i.e., 16K entries
	 * in MSMC SRAM), the actual memory used is 0x0c000000-0x0c020000,
	 * which accounts for 64-bits per entry, for 16K entries.
	 */
	if (!of_property_read_u32_array(node, name , temp, 2)) {
		if (temp[0]) {
			/*
			 * queue_base specified => using internal or onchip
			 * link ram WARNING - we do not "reserve" this block
			 */
			block->dma = (dma_addr_t)temp[0];
			block->virt = NULL;
			block->size = temp[1];
		} else {
			block->size = temp[1];
			/* queue_base not specific => allocate requested size */
			block->virt = dmam_alloc_coherent(kdev->dev,
						  8 * block->size, &block->dma,
						  GFP_KERNEL);
			if (!block->virt) {
				dev_err(kdev->dev, "failed to alloc linkram\n");
				return -ENOMEM;
			}
		}
	} else {
		return -ENODEV;
	}
	return 0;
}