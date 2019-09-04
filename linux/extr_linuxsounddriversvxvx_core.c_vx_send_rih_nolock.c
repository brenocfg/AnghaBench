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
struct vx_core {int chip_status; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ISR ; 
 int /*<<< orphan*/  ISR_CHK ; 
 int ISR_ERR ; 
 int /*<<< orphan*/  RXH ; 
 int /*<<< orphan*/  RXL ; 
 int /*<<< orphan*/  RXM ; 
 int VX_ERR_MASK ; 
 int VX_STAT_IS_STALE ; 
 int vx_inb (struct vx_core*,int /*<<< orphan*/ ) ; 
 int vx_reset_chk (struct vx_core*) ; 
 int vx_send_irq_dsp (struct vx_core*,int) ; 
 int vx_wait_for_rx_full (struct vx_core*) ; 
 int vx_wait_isr_bit (struct vx_core*,int /*<<< orphan*/ ) ; 

int vx_send_rih_nolock(struct vx_core *chip, int cmd)
{
	int err;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;

#if 0
	printk(KERN_DEBUG "send_rih: cmd = 0x%x\n", cmd);
#endif
	if ((err = vx_reset_chk(chip)) < 0)
		return err;
	/* send the IRQ */
	if ((err = vx_send_irq_dsp(chip, cmd)) < 0)
		return err;
	/* Wait CHK = 1 */
	if ((err = vx_wait_isr_bit(chip, ISR_CHK)) < 0)
		return err;
	/* If error, read RX */
	if (vx_inb(chip, ISR) & ISR_ERR) {
		if ((err = vx_wait_for_rx_full(chip)) < 0)
			return err;
		err = vx_inb(chip, RXH) << 16;
		err |= vx_inb(chip, RXM) << 8;
		err |= vx_inb(chip, RXL);
		return -(VX_ERR_MASK | err);
	}
	return 0;
}