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
struct uart_port {int dummy; } ;

/* Variables and functions */
 unsigned int S3C2410_UMCOM_RTS_LOW ; 
 int /*<<< orphan*/  S3C2410_UMCON ; 
 unsigned int TIOCM_RTS ; 
 unsigned int rd_regl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_regl (struct uart_port*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void s3c24xx_serial_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	unsigned int umcon = rd_regl(port, S3C2410_UMCON);

	if (mctrl & TIOCM_RTS)
		umcon |= S3C2410_UMCOM_RTS_LOW;
	else
		umcon &= ~S3C2410_UMCOM_RTS_LOW;

	wr_regl(port, S3C2410_UMCON, umcon);
}