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
typedef  int /*<<< orphan*/  u32 ;
struct uart_port {int dummy; } ;
struct s3c24xx_uart_port {void* tx_mode; int /*<<< orphan*/  tx_irq; void* tx_in_progress; struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_UCON ; 
 int /*<<< orphan*/  S3C2410_UFCON ; 
 void* S3C24XX_TX_PIO ; 
 int /*<<< orphan*/  S3C64XX_UCON_TXMODE_CPU ; 
 int /*<<< orphan*/  S3C64XX_UCON_TXMODE_MASK ; 
 int /*<<< orphan*/  S3C64XX_UINTM ; 
 int /*<<< orphan*/  S3C64XX_UINTM_TXD ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c24xx_clear_bit (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ s3c24xx_serial_has_interrupt_mask (struct uart_port*) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_tx_pio(struct s3c24xx_uart_port *ourport)
{
	struct uart_port *port = &ourport->port;
	u32 ucon, ufcon;

	/* Set ufcon txtrig */
	ourport->tx_in_progress = S3C24XX_TX_PIO;
	ufcon = rd_regl(port, S3C2410_UFCON);
	wr_regl(port,  S3C2410_UFCON, ufcon);

	/* Enable tx pio mode */
	ucon = rd_regl(port, S3C2410_UCON);
	ucon &= ~(S3C64XX_UCON_TXMODE_MASK);
	ucon |= S3C64XX_UCON_TXMODE_CPU;
	wr_regl(port,  S3C2410_UCON, ucon);

	/* Unmask Tx interrupt */
	if (s3c24xx_serial_has_interrupt_mask(port))
		s3c24xx_clear_bit(port, S3C64XX_UINTM_TXD,
				  S3C64XX_UINTM);
	else
		enable_irq(ourport->tx_irq);

	ourport->tx_mode = S3C24XX_TX_PIO;
}