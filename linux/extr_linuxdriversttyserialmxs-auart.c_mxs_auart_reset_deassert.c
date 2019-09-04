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
struct mxs_auart_port {int dummy; } ;

/* Variables and functions */
 unsigned int AUART_CTRL0_CLKGATE ; 
 unsigned int AUART_CTRL0_SFTRST ; 
 int /*<<< orphan*/  REG_CTRL0 ; 
 int /*<<< orphan*/  mxs_clr (unsigned int,struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 unsigned int mxs_read (struct mxs_auart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mxs_auart_reset_deassert(struct mxs_auart_port *s)
{
	int i;
	unsigned int reg;

	mxs_clr(AUART_CTRL0_SFTRST, s, REG_CTRL0);

	for (i = 0; i < 10000; i++) {
		reg = mxs_read(s, REG_CTRL0);
		if (!(reg & AUART_CTRL0_SFTRST))
			break;
		udelay(3);
	}
	mxs_clr(AUART_CTRL0_CLKGATE, s, REG_CTRL0);
}