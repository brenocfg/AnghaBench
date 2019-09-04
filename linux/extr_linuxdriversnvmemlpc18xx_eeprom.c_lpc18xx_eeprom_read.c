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
struct lpc18xx_eeprom_dev {scalar_t__ val_bytes; scalar_t__ mem_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN_NO ; 
 int /*<<< orphan*/  LPC18XX_EEPROM_PWRDWN_YES ; 
 int /*<<< orphan*/  lpc18xx_eeprom_writel (struct lpc18xx_eeprom_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lpc18xx_eeprom_read(void *context, unsigned int offset,
			       void *val, size_t bytes)
{
	struct lpc18xx_eeprom_dev *eeprom = context;

	lpc18xx_eeprom_writel(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_NO);

	/* Wait 100 us while the EEPROM wakes up */
	usleep_range(100, 200);

	while (bytes) {
		*(u32 *)val = readl(eeprom->mem_base + offset);
		bytes -= eeprom->val_bytes;
		val += eeprom->val_bytes;
		offset += eeprom->val_bytes;
	}

	lpc18xx_eeprom_writel(eeprom, LPC18XX_EEPROM_PWRDWN,
			      LPC18XX_EEPROM_PWRDWN_YES);

	return 0;
}