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
struct parport {int dummy; } ;

/* Variables and functions */
 int ESTB ; 
 scalar_t__ RXDATA0 ; 
 scalar_t__ STROBE ; 
 scalar_t__ TXDATA0 ; 
 int TXEMPTY ; 
 int parport_read_status (struct parport*) ; 
 int /*<<< orphan*/  parport_write_control (struct parport*,scalar_t__) ; 
 int /*<<< orphan*/  parport_write_data (struct parport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int portman_probe(struct parport *p)
{
	/* Initialize the parallel port data register.  Will set Rx clocks
	 * low in case we happen to be addressing the Rx ports at this time.
	 */
	/* 1 */
	parport_write_data(p, 0);

	/* Initialize the parallel port command register, thus initializing
	 * hardware handshake lines to midi box:
	 *
	 *                                  Strobe = 0
	 *                                  Interrupt Enable = 0            
	 */
	/* 2 */
	parport_write_control(p, 0);

	/* Check if Portman PC/P 2x4 is out there. */
	/* 3 */
	parport_write_control(p, RXDATA0);	/* Write Strobe=0 to command reg. */

	/* Check for ESTB to be clear */
	/* 4 */
	if ((parport_read_status(p) & ESTB) == ESTB)
		return 1;	/* CODE 1 - Strobe Failure. */

	/* Set for RXDATA0 where no damage will be done. */
	/* 5 */
	parport_write_control(p, RXDATA0 + STROBE);	/* Write Strobe=1 to command reg. */

	/* 6 */
	if ((parport_read_status(p) & ESTB) != ESTB)
		return 1;	/* CODE 1 - Strobe Failure. */

	/* 7 */
	parport_write_control(p, 0);	/* Reset Strobe=0. */

	/* Check if Tx circuitry is functioning properly.  If initialized 
	 * unit TxEmpty is false, send out char and see if if goes true.
	 */
	/* 8 */
	parport_write_control(p, TXDATA0);	/* Tx channel 0, strobe off. */

	/* If PCP channel's TxEmpty is set (TxEmpty is read through the PP
	 * Status Register), then go write data.  Else go back and wait.
	 */
	/* 9 */
	if ((parport_read_status(p) & TXEMPTY) == 0)
		return 2;

	/* Return OK status. */
	return 0;
}