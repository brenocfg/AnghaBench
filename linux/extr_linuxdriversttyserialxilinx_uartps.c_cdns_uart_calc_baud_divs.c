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

/* Variables and functions */
 int CDNS_UART_BDIV_MAX ; 
 int CDNS_UART_BDIV_MIN ; 
 int CDNS_UART_CD_MAX ; 
 int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int cdns_uart_calc_baud_divs(unsigned int clk,
		unsigned int baud, u32 *rbdiv, u32 *rcd, int *div8)
{
	u32 cd, bdiv;
	unsigned int calc_baud;
	unsigned int bestbaud = 0;
	unsigned int bauderror;
	unsigned int besterror = ~0;

	if (baud < clk / ((CDNS_UART_BDIV_MAX + 1) * CDNS_UART_CD_MAX)) {
		*div8 = 1;
		clk /= 8;
	} else {
		*div8 = 0;
	}

	for (bdiv = CDNS_UART_BDIV_MIN; bdiv <= CDNS_UART_BDIV_MAX; bdiv++) {
		cd = DIV_ROUND_CLOSEST(clk, baud * (bdiv + 1));
		if (cd < 1 || cd > CDNS_UART_CD_MAX)
			continue;

		calc_baud = clk / (cd * (bdiv + 1));

		if (baud > calc_baud)
			bauderror = baud - calc_baud;
		else
			bauderror = calc_baud - baud;

		if (besterror > bauderror) {
			*rbdiv = bdiv;
			*rcd = cd;
			bestbaud = calc_baud;
			besterror = bauderror;
		}
	}
	/* use the values when percent error is acceptable */
	if (((besterror * 100) / baud) < 3)
		bestbaud = baud;

	return bestbaud;
}