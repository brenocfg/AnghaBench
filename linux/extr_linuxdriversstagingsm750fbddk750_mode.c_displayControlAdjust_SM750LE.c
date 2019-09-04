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
struct mode_parameter {unsigned long horizontal_display_end; unsigned long vertical_display_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_AUTO_CENTERING_BR ; 
 unsigned long CRT_AUTO_CENTERING_BR_BOTTOM_MASK ; 
 unsigned long CRT_AUTO_CENTERING_BR_BOTTOM_SHIFT ; 
 unsigned long CRT_AUTO_CENTERING_BR_RIGHT_MASK ; 
 int /*<<< orphan*/  CRT_AUTO_CENTERING_TL ; 
 int /*<<< orphan*/  CRT_DISPLAY_CTRL ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_MASK ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL108 ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL25 ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL41 ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL65 ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL74 ; 
 unsigned long CRT_DISPLAY_CTRL_CLK_PLL80 ; 
 unsigned long CRT_DISPLAY_CTRL_CRTSELECT ; 
 unsigned long CRT_DISPLAY_CTRL_RGBBIT ; 
 unsigned long DISPLAY_CTRL_CLOCK_PHASE ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned long displayControlAdjust_SM750LE(struct mode_parameter *pModeParam,
						  unsigned long dispControl)
{
	unsigned long x, y;

	x = pModeParam->horizontal_display_end;
	y = pModeParam->vertical_display_end;

	/*
	 * SM750LE has to set up the top-left and bottom-right
	 * registers as well.
	 * Note that normal SM750/SM718 only use those two register for
	 * auto-centering mode.
	 */
	poke32(CRT_AUTO_CENTERING_TL, 0);

	poke32(CRT_AUTO_CENTERING_BR,
	       (((y - 1) << CRT_AUTO_CENTERING_BR_BOTTOM_SHIFT) &
		CRT_AUTO_CENTERING_BR_BOTTOM_MASK) |
	       ((x - 1) & CRT_AUTO_CENTERING_BR_RIGHT_MASK));

	/*
	 * Assume common fields in dispControl have been properly set before
	 * calling this function.
	 * This function only sets the extra fields in dispControl.
	 */

	/* Clear bit 29:27 of display control register */
	dispControl &= ~CRT_DISPLAY_CTRL_CLK_MASK;

	/* Set bit 29:27 of display control register for the right clock */
	/* Note that SM750LE only need to supported 7 resolutions. */
	if (x == 800 && y == 600)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL41;
	else if (x == 1024 && y == 768)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL65;
	else if (x == 1152 && y == 864)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL80;
	else if (x == 1280 && y == 768)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL80;
	else if (x == 1280 && y == 720)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL74;
	else if (x == 1280 && y == 960)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL108;
	else if (x == 1280 && y == 1024)
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL108;
	else /* default to VGA clock */
		dispControl |= CRT_DISPLAY_CTRL_CLK_PLL25;

	/* Set bit 25:24 of display controller */
	dispControl |= (CRT_DISPLAY_CTRL_CRTSELECT | CRT_DISPLAY_CTRL_RGBBIT);

	/* Set bit 14 of display controller */
	dispControl |= DISPLAY_CTRL_CLOCK_PHASE;

	poke32(CRT_DISPLAY_CTRL, dispControl);

	return dispControl;
}