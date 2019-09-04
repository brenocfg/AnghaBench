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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC16IS7XX_EFCR_REG ; 
 int SC16IS7XX_EFCR_RXDISABLE_BIT ; 
 int SC16IS7XX_EFCR_TXDISABLE_BIT ; 
 unsigned int SC16IS7XX_EFR_ENABLE_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_EFR_REG ; 
 unsigned int SC16IS7XX_FCR_FIFO_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_FCR_REG ; 
 unsigned int SC16IS7XX_FCR_RXRESET_BIT ; 
 unsigned int SC16IS7XX_FCR_TXRESET_BIT ; 
 unsigned int SC16IS7XX_IER_RDI_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_IER_REG ; 
 unsigned int SC16IS7XX_IER_THRI_BIT ; 
 unsigned int SC16IS7XX_LCR_CONF_MODE_B ; 
 int /*<<< orphan*/  SC16IS7XX_LCR_REG ; 
 unsigned int SC16IS7XX_LCR_WORD_LEN_8 ; 
 int /*<<< orphan*/  SC16IS7XX_MCR_REG ; 
 int SC16IS7XX_MCR_TCRTLR_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_TCR_REG ; 
 unsigned int SC16IS7XX_TCR_RX_HALT (int) ; 
 unsigned int SC16IS7XX_TCR_RX_RESUME (int) ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cache_bypass (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc16is7xx_port_update (struct uart_port*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sc16is7xx_port_write (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sc16is7xx_power (struct uart_port*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sc16is7xx_startup(struct uart_port *port)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	unsigned int val;

	sc16is7xx_power(port, 1);

	/* Reset FIFOs*/
	val = SC16IS7XX_FCR_RXRESET_BIT | SC16IS7XX_FCR_TXRESET_BIT;
	sc16is7xx_port_write(port, SC16IS7XX_FCR_REG, val);
	udelay(5);
	sc16is7xx_port_write(port, SC16IS7XX_FCR_REG,
			     SC16IS7XX_FCR_FIFO_BIT);

	/* Enable EFR */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_B);

	regcache_cache_bypass(s->regmap, true);

	/* Enable write access to enhanced features and internal clock div */
	sc16is7xx_port_write(port, SC16IS7XX_EFR_REG,
			     SC16IS7XX_EFR_ENABLE_BIT);

	/* Enable TCR/TLR */
	sc16is7xx_port_update(port, SC16IS7XX_MCR_REG,
			      SC16IS7XX_MCR_TCRTLR_BIT,
			      SC16IS7XX_MCR_TCRTLR_BIT);

	/* Configure flow control levels */
	/* Flow control halt level 48, resume level 24 */
	sc16is7xx_port_write(port, SC16IS7XX_TCR_REG,
			     SC16IS7XX_TCR_RX_RESUME(24) |
			     SC16IS7XX_TCR_RX_HALT(48));

	regcache_cache_bypass(s->regmap, false);

	/* Now, initialize the UART */
	sc16is7xx_port_write(port, SC16IS7XX_LCR_REG, SC16IS7XX_LCR_WORD_LEN_8);

	/* Enable the Rx and Tx FIFO */
	sc16is7xx_port_update(port, SC16IS7XX_EFCR_REG,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT,
			      0);

	/* Enable RX, TX interrupts */
	val = SC16IS7XX_IER_RDI_BIT | SC16IS7XX_IER_THRI_BIT;
	sc16is7xx_port_write(port, SC16IS7XX_IER_REG, val);

	return 0;
}