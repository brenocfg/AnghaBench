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
struct atiixp_modem {int dummy; } ;

/* Variables and functions */
 unsigned int ATI_REG_CMD_BURST_EN ; 
 unsigned int ATI_REG_CMD_MODEM_PRESENT ; 
 int ATI_REG_IER_MODEM_IN_XRUN_EN ; 
 int ATI_REG_IER_MODEM_OUT1_XRUN_EN ; 
 int ATI_REG_IER_MODEM_STATUS_EN ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  ISR ; 
 unsigned int atiixp_read (struct atiixp_modem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_write (struct atiixp_modem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int snd_atiixp_chip_start(struct atiixp_modem *chip)
{
	unsigned int reg;

	/* set up spdif, enable burst mode */
	reg = atiixp_read(chip, CMD);
	reg |= ATI_REG_CMD_BURST_EN;
	if(!(reg & ATI_REG_CMD_MODEM_PRESENT))
		reg |= ATI_REG_CMD_MODEM_PRESENT;
	atiixp_write(chip, CMD, reg);

	/* clear all interrupt source */
	atiixp_write(chip, ISR, 0xffffffff);
	/* enable irqs */
	atiixp_write(chip, IER,
		     ATI_REG_IER_MODEM_STATUS_EN |
		     ATI_REG_IER_MODEM_IN_XRUN_EN |
		     ATI_REG_IER_MODEM_OUT1_XRUN_EN);
	return 0;
}