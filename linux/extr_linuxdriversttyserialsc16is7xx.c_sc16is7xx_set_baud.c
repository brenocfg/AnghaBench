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
typedef  unsigned long u8 ;
struct uart_port {unsigned long uartclk; int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  regmap; int /*<<< orphan*/  efr_lock; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  SC16IS7XX_DLH_REG ; 
 int /*<<< orphan*/  SC16IS7XX_DLL_REG ; 
 unsigned long SC16IS7XX_EFR_ENABLE_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_EFR_REG ; 
 unsigned long SC16IS7XX_LCR_CONF_MODE_A ; 
 unsigned long SC16IS7XX_LCR_CONF_MODE_B ; 
 int /*<<< orphan*/  SC16IS7XX_LCR_REG ; 
 unsigned long SC16IS7XX_MCR_CLKSEL_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_MCR_REG ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 unsigned long sc16is7xx_port_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_port_update (struct uart_port*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  sc16is7xx_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int sc16is7xx_set_baud(struct uart_port *port, int baud)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	u8 lcr;
	u8 prescaler = 0;
	unsigned long clk = port->uartclk, div = clk / 16 / baud;

	if (div > 0xffff) {
		prescaler = SC16IS7XX_MCR_CLKSEL_BIT;
		div /= 4;
	}

	/* In an amazing feat of design, the Enhanced Features Register shares
	 * the address of the Interrupt Identification Register, and is
	 * switched in by writing a magic value (0xbf) to the Line Control
	 * Register. Any interrupt firing during this time will see the EFR
	 * where it expects the IIR to be, leading to "Unexpected interrupt"
	 * messages.
	 *
	 * Prevent this possibility by claiming a mutex while accessing the
	 * EFR, and claiming the same mutex from within the interrupt handler.
	 * This is similar to disabling the interrupt, but that doesn't work
	 * because the bulk of the interrupt processing is run as a workqueue
	 * job in thread context.
	 */
	mutex_lock(&s->efr_lock);

	lcr = sc16is7xx_port_read(port, SC16IS7XX_LCR_REG);

	/* Open the LCR divisors for configuration */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_B);

	/* Enable enhanced features */
	regcache_cache_bypass(s->regmap, true);
	sc16is7xx_port_write(port, SC16IS7XX_EFR_REG,
			     SC16IS7XX_EFR_ENABLE_BIT);
	regcache_cache_bypass(s->regmap, false);

	/* Put LCR back to the normal mode */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG, lcr);

	mutex_unlock(&s->efr_lock);

	sc16is7xx_port_update(port, SC16IS7XX_MCR_REG,
			      SC16IS7XX_MCR_CLKSEL_BIT,
			      prescaler);

	/* Open the LCR divisors for configuration */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_A);

	/* Write the new divisor */
	regcache_cache_bypass(s->regmap, true);
	sc16is7xx_port_write(port, SC16IS7XX_DLH_REG, div / 256);
	sc16is7xx_port_write(port, SC16IS7XX_DLL_REG, div % 256);
	regcache_cache_bypass(s->regmap, false);

	/* Put LCR back to the normal mode */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG, lcr);

	return DIV_ROUND_CLOSEST(clk / 16, div);
}