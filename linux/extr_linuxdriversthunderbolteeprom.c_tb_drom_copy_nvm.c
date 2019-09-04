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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct tb_switch {int* drom; int /*<<< orphan*/  uid; int /*<<< orphan*/  dma_port; scalar_t__ cap_plug_events; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TB_CFG_SWITCH ; 
 int dma_port_flash_read (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_drom_read_uid_only (struct tb_switch*,int /*<<< orphan*/ *) ; 
 int tb_sw_read (struct tb_switch*,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int tb_drom_copy_nvm(struct tb_switch *sw, u16 *size)
{
	u32 drom_offset;
	int ret;

	if (!sw->dma_port)
		return -ENODEV;

	ret = tb_sw_read(sw, &drom_offset, TB_CFG_SWITCH,
			 sw->cap_plug_events + 12, 1);
	if (ret)
		return ret;

	if (!drom_offset)
		return -ENODEV;

	ret = dma_port_flash_read(sw->dma_port, drom_offset + 14, size,
				  sizeof(*size));
	if (ret)
		return ret;

	/* Size includes CRC8 + UID + CRC32 */
	*size += 1 + 8 + 4;
	sw->drom = kzalloc(*size, GFP_KERNEL);
	if (!sw->drom)
		return -ENOMEM;

	ret = dma_port_flash_read(sw->dma_port, drom_offset, sw->drom, *size);
	if (ret)
		goto err_free;

	/*
	 * Read UID from the minimal DROM because the one in NVM is just
	 * a placeholder.
	 */
	tb_drom_read_uid_only(sw, &sw->uid);
	return 0;

err_free:
	kfree(sw->drom);
	sw->drom = NULL;
	return ret;
}