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
struct vx_core {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQ_RESET_CHK ; 
 int /*<<< orphan*/  ISR_CHK ; 
 scalar_t__ vx_check_isr (struct vx_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vx_send_irq_dsp (struct vx_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_reset_chk(struct vx_core *chip)
{
	/* Reset irq CHK */
	if (vx_send_irq_dsp(chip, IRQ_RESET_CHK) < 0)
		return -EIO;
	/* Wait until CHK = 0 */
	if (vx_check_isr(chip, ISR_CHK, 0, 200) < 0)
		return -EIO;
	return 0;
}