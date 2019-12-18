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
typedef  int /*<<< orphan*/  u16 ;
struct snd_pdacf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDAUDIOCF_PDN ; 
 int /*<<< orphan*/  PDAUDIOCF_RECORD ; 
 int /*<<< orphan*/  PDAUDIOCF_REG_SCR ; 
 int /*<<< orphan*/  PDAUDIOCF_RST ; 
 int /*<<< orphan*/  pdacf_reg_read (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdacf_reg_write (struct snd_pdacf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int pdacf_reset(struct snd_pdacf *chip, int powerdown)
{
	u16 val;
	
	val = pdacf_reg_read(chip, PDAUDIOCF_REG_SCR);
	val |= PDAUDIOCF_PDN;
	val &= ~PDAUDIOCF_RECORD;		/* for sure */
	pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, val);
	udelay(5);
	val |= PDAUDIOCF_RST;
	pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, val);
	udelay(200);
	val &= ~PDAUDIOCF_RST;
	pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, val);
	udelay(5);
	if (!powerdown) {
		val &= ~PDAUDIOCF_PDN;
		pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, val);
		udelay(200);
	}
	return 0;
}