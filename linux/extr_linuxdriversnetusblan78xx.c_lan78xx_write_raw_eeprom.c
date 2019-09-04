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
typedef  int u8 ;
typedef  int u32 ;
struct lan78xx_net {scalar_t__ chipid; } ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_CMD ; 
 int E2P_CMD_EPC_ADDR_MASK_ ; 
 int E2P_CMD_EPC_BUSY_ ; 
 int E2P_CMD_EPC_CMD_EWEN_ ; 
 int E2P_CMD_EPC_CMD_WRITE_ ; 
 int /*<<< orphan*/  E2P_DATA ; 
 int EIO ; 
 int /*<<< orphan*/  HW_CFG ; 
 int HW_CFG_LED0_EN_ ; 
 int HW_CFG_LED1_EN_ ; 
 scalar_t__ ID_REV_CHIP_ID_7800_ ; 
 int lan78xx_eeprom_confirm_not_busy (struct lan78xx_net*) ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_wait_eeprom (struct lan78xx_net*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lan78xx_write_raw_eeprom(struct lan78xx_net *dev, u32 offset,
				    u32 length, u8 *data)
{
	u32 val;
	u32 saved;
	int i, ret;
	int retval;

	/* depends on chip, some EEPROM pins are muxed with LED function.
	 * disable & restore LED function to access EEPROM.
	 */
	ret = lan78xx_read_reg(dev, HW_CFG, &val);
	saved = val;
	if (dev->chipid == ID_REV_CHIP_ID_7800_) {
		val &= ~(HW_CFG_LED1_EN_ | HW_CFG_LED0_EN_);
		ret = lan78xx_write_reg(dev, HW_CFG, val);
	}

	retval = lan78xx_eeprom_confirm_not_busy(dev);
	if (retval)
		goto exit;

	/* Issue write/erase enable command */
	val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_EWEN_;
	ret = lan78xx_write_reg(dev, E2P_CMD, val);
	if (unlikely(ret < 0)) {
		retval = -EIO;
		goto exit;
	}

	retval = lan78xx_wait_eeprom(dev);
	if (retval < 0)
		goto exit;

	for (i = 0; i < length; i++) {
		/* Fill data register */
		val = data[i];
		ret = lan78xx_write_reg(dev, E2P_DATA, val);
		if (ret < 0) {
			retval = -EIO;
			goto exit;
		}

		/* Send "write" command */
		val = E2P_CMD_EPC_BUSY_ | E2P_CMD_EPC_CMD_WRITE_;
		val |= (offset & E2P_CMD_EPC_ADDR_MASK_);
		ret = lan78xx_write_reg(dev, E2P_CMD, val);
		if (ret < 0) {
			retval = -EIO;
			goto exit;
		}

		retval = lan78xx_wait_eeprom(dev);
		if (retval < 0)
			goto exit;

		offset++;
	}

	retval = 0;
exit:
	if (dev->chipid == ID_REV_CHIP_ID_7800_)
		ret = lan78xx_write_reg(dev, HW_CFG, saved);

	return retval;
}