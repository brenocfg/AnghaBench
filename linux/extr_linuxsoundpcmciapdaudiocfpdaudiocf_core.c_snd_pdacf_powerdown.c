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
typedef  int u16 ;
struct snd_pdacf {int suspend_reg_scr; scalar_t__ port; } ;

/* Variables and functions */
 int PDAUDIOCF_BLUE_LED_OFF ; 
 int PDAUDIOCF_IRQAKMEN ; 
 int PDAUDIOCF_IRQLVLEN0 ; 
 int PDAUDIOCF_IRQLVLEN1 ; 
 int PDAUDIOCF_IRQOVREN ; 
 int PDAUDIOCF_RED_LED_OFF ; 
 scalar_t__ PDAUDIOCF_REG_IER ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_SCR ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int pdacf_reg_read (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdacf_reg_write (struct snd_pdacf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdacf_reset (struct snd_pdacf*,int) ; 

void snd_pdacf_powerdown(struct snd_pdacf *chip)
{
	u16 val;

	val = pdacf_reg_read(chip, PDAUDIOCF_REG_SCR);
	chip->suspend_reg_scr = val;
	val |= PDAUDIOCF_RED_LED_OFF | PDAUDIOCF_BLUE_LED_OFF;
	pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, val);
	/* disable interrupts, but use direct write to preserve old register value in chip->regmap */
	val = inw(chip->port + PDAUDIOCF_REG_IER);
	val &= ~(PDAUDIOCF_IRQOVREN|PDAUDIOCF_IRQAKMEN|PDAUDIOCF_IRQLVLEN0|PDAUDIOCF_IRQLVLEN1);
	outw(val, chip->port + PDAUDIOCF_REG_IER);
	pdacf_reset(chip, 1);
}