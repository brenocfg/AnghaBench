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
struct s3c24xx_uart_port {scalar_t__ tx_mode; } ;

/* Variables and functions */
 scalar_t__ S3C24XX_TX_PIO ; 
 int /*<<< orphan*/  enable_tx_pio (struct s3c24xx_uart_port*) ; 

__attribute__((used)) static void s3c24xx_serial_start_tx_pio(struct s3c24xx_uart_port *ourport)
{
	if (ourport->tx_mode != S3C24XX_TX_PIO)
		enable_tx_pio(ourport);
}