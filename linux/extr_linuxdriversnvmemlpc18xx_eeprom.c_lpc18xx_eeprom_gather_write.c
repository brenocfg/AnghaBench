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
typedef  int /*<<< orphan*/  u32 ;
struct lpc18xx_eeprom_dev {unsigned int size; scalar_t__ val_bytes; scalar_t__ mem_base; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LPC18XX_EEPROM_PAGE_SIZE ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN_NO ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN_YES ; 
 int lpc18xx_eeprom_busywait_until_prog (struct lpc18xx_eeprom_dev*) ; 
 int /*<<< orphan*/  lpc18xx_eeprom_writel (struct lpc18xx_eeprom_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_eeprom_gather_write(void *context, unsigned int reg,
				       void *val, size_t bytes)
{
	struct lpc18xx_eeprom_dev *eeprom = context;
	unsigned int offset = reg;
	int ret;

	/*
	 * The last page contains the EEPROM initialization data and is not
	 * writable.
	 */
	if ((reg > eeprom->size - LPC18XX_EEPROM_PAGE_SIZE) ||
			(reg + bytes > eeprom->size - LPC18XX_EEPROM_PAGE_SIZE))
		return -EINVAL;


	lpc18xx_eeprom_writel(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_NO);

	/* Wait 100 us while the EEPROM wakes up */
	usleep_range(100, 200);

	while (bytes) {
		writel(*(u32 *)val, eeprom->mem_base + offset);
		ret = lpc18xx_eeprom_busywait_until_prog(eeprom);
		if (ret < 0)
			return ret;

		bytes -= eeprom->val_bytes;
		val += eeprom->val_bytes;
		offset += eeprom->val_bytes;
	}

	lpc18xx_eeprom_writel(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_YES);

	return 0;
}