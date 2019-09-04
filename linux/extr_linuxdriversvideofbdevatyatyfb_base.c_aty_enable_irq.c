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
typedef  int u32 ;
struct atyfb_par {int /*<<< orphan*/  int_lock; int /*<<< orphan*/  irq_flags; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC_INT_CNTL ; 
 int CRTC_INT_EN_MASK ; 
 int CRTC_VBLANK_INT_AK ; 
 int CRTC_VBLANK_INT_EN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  aty_irq ; 
 int aty_ld_le32 (int /*<<< orphan*/ ,struct atyfb_par*) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct atyfb_par*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aty_enable_irq(struct atyfb_par *par, int reenable)
{
	u32 int_cntl;

	if (!test_and_set_bit(0, &par->irq_flags)) {
		if (request_irq(par->irq, aty_irq, IRQF_SHARED, "atyfb", par)) {
			clear_bit(0, &par->irq_flags);
			return -EINVAL;
		}
		spin_lock_irq(&par->int_lock);
		int_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		/* clear interrupt */
		aty_st_le32(CRTC_INT_CNTL, int_cntl | CRTC_VBLANK_INT_AK, par);
		/* enable interrupt */
		aty_st_le32(CRTC_INT_CNTL, int_cntl | CRTC_VBLANK_INT_EN, par);
		spin_unlock_irq(&par->int_lock);
	} else if (reenable) {
		spin_lock_irq(&par->int_lock);
		int_cntl = aty_ld_le32(CRTC_INT_CNTL, par) & CRTC_INT_EN_MASK;
		if (!(int_cntl & CRTC_VBLANK_INT_EN)) {
			printk("atyfb: someone disabled IRQ [%08x]\n",
			       int_cntl);
			/* re-enable interrupt */
			aty_st_le32(CRTC_INT_CNTL, int_cntl |
				    CRTC_VBLANK_INT_EN, par);
		}
		spin_unlock_irq(&par->int_lock);
	}

	return 0;
}