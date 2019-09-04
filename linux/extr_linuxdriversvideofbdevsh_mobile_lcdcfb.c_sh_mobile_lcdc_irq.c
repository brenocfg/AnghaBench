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
struct sh_mobile_lcdc_priv {struct sh_mobile_lcdc_chan* ch; } ;
struct sh_mobile_lcdc_chan {int frame_end; int /*<<< orphan*/  vsync_completion; int /*<<< orphan*/  frame_end_wait; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int ARRAY_SIZE (struct sh_mobile_lcdc_chan*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long LDINTR_FS ; 
 unsigned long LDINTR_STATUS_MASK ; 
 unsigned long LDINTR_VEE ; 
 unsigned long LDINTR_VES ; 
 int LDSR_MSS ; 
 int /*<<< orphan*/  _LDINTR ; 
 int /*<<< orphan*/  _LDSR ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int lcdc_chan_is_sublcd (struct sh_mobile_lcdc_chan*) ; 
 int lcdc_read (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct sh_mobile_lcdc_priv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_clk_off (struct sh_mobile_lcdc_priv*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sh_mobile_lcdc_irq(int irq, void *data)
{
	struct sh_mobile_lcdc_priv *priv = data;
	struct sh_mobile_lcdc_chan *ch;
	unsigned long ldintr;
	int is_sub;
	int k;

	/* Acknowledge interrupts and disable further VSYNC End IRQs. */
	ldintr = lcdc_read(priv, _LDINTR);
	lcdc_write(priv, _LDINTR, (ldintr ^ LDINTR_STATUS_MASK) & ~LDINTR_VEE);

	/* figure out if this interrupt is for main or sub lcd */
	is_sub = (lcdc_read(priv, _LDSR) & LDSR_MSS) ? 1 : 0;

	/* wake up channel and disable clocks */
	for (k = 0; k < ARRAY_SIZE(priv->ch); k++) {
		ch = &priv->ch[k];

		if (!ch->enabled)
			continue;

		/* Frame End */
		if (ldintr & LDINTR_FS) {
			if (is_sub == lcdc_chan_is_sublcd(ch)) {
				ch->frame_end = 1;
				wake_up(&ch->frame_end_wait);

				sh_mobile_lcdc_clk_off(priv);
			}
		}

		/* VSYNC End */
		if (ldintr & LDINTR_VES)
			complete(&ch->vsync_completion);
	}

	return IRQ_HANDLED;
}