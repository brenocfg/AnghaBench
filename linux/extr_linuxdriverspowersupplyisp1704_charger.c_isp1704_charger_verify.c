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
typedef  int u8 ;
struct isp1704_charger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1704_PWR_CTRL ; 
 int ISP1704_PWR_CTRL_DP_WKPU_EN ; 
 int /*<<< orphan*/  ULPI_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ULPI_DEBUG ; 
 int /*<<< orphan*/  ULPI_FUNC_CTRL ; 
 int ULPI_FUNC_CTRL_OPMODE_MASK ; 
 int ULPI_FUNC_CTRL_RESET ; 
 int ULPI_FUNC_CTRL_TERMSELECT ; 
 int /*<<< orphan*/  ULPI_OTG_CTRL ; 
 int ULPI_OTG_CTRL_DM_PULLDOWN ; 
 int ULPI_OTG_CTRL_DP_PULLDOWN ; 
 int /*<<< orphan*/  ULPI_SET (int /*<<< orphan*/ ) ; 
 int isp1704_read (struct isp1704_charger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1704_write (struct isp1704_charger*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int isp1704_charger_verify(struct isp1704_charger *isp)
{
	int	ret = 0;
	u8	r;

	/* Reset the transceiver */
	r = isp1704_read(isp, ULPI_FUNC_CTRL);
	r |= ULPI_FUNC_CTRL_RESET;
	isp1704_write(isp, ULPI_FUNC_CTRL, r);
	usleep_range(1000, 2000);

	/* Set normal mode */
	r &= ~(ULPI_FUNC_CTRL_RESET | ULPI_FUNC_CTRL_OPMODE_MASK);
	isp1704_write(isp, ULPI_FUNC_CTRL, r);

	/* Clear the DP and DM pull-down bits */
	r = ULPI_OTG_CTRL_DP_PULLDOWN | ULPI_OTG_CTRL_DM_PULLDOWN;
	isp1704_write(isp, ULPI_CLR(ULPI_OTG_CTRL), r);

	/* Enable strong pull-up on DP (1.5K) and reset */
	r = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL), r);
	usleep_range(1000, 2000);

	/* Read the line state */
	if (!isp1704_read(isp, ULPI_DEBUG)) {
		/* Disable strong pull-up on DP (1.5K) */
		isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
				ULPI_FUNC_CTRL_TERMSELECT);
		return 1;
	}

	/* Is it a charger or PS/2 connection */

	/* Enable weak pull-up resistor on DP */
	isp1704_write(isp, ULPI_SET(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	/* Disable strong pull-up on DP (1.5K) */
	isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_TERMSELECT);

	/* Enable weak pull-down resistor on DM */
	isp1704_write(isp, ULPI_SET(ULPI_OTG_CTRL),
			ULPI_OTG_CTRL_DM_PULLDOWN);

	/* It's a charger if the line states are clear */
	if (!(isp1704_read(isp, ULPI_DEBUG)))
		ret = 1;

	/* Disable weak pull-up resistor on DP */
	isp1704_write(isp, ULPI_CLR(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	return ret;
}