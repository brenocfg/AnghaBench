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
struct mxs_auart_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUART_CTRL0_CLKGATE ; 
 int AUART_CTRL0_SFTRST ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mxs_clr (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxs_set (int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mxs_auart_reset_assert(struct mxs_auart_port *s)
{
	int i;
	u32 reg;

	reg = mxs_read(s, REG_CTRL0);
	/* if already in reset state, keep it untouched */
	if (reg & AUART_CTRL0_SFTRST)
		return;

	mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
	mxs_set(AUART_CTRL0_SFTRST, s, REG_CTRL0);

	for (i = 0; i < 1000; i++) {
		reg = mxs_read(s, REG_CTRL0);
		/* reset is finished when the clock is gated */
		if (reg & AUART_CTRL0_CLKGATE)
			return;
		udelay(10);
	}

	dev_err(s->dev, "Failed to reset the unit.");
}