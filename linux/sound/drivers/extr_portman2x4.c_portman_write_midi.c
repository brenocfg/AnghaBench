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
typedef  int /*<<< orphan*/  u8 ;
struct portman {int dummy; } ;

/* Variables and functions */
 int BUSY ; 
 int ESTB ; 
 int INT_EN ; 
 int STROBE ; 
 int TXEMPTY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int portman_read_status (struct portman*) ; 
 int /*<<< orphan*/  portman_write_command (struct portman*,int) ; 
 int /*<<< orphan*/  portman_write_data (struct portman*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void portman_write_midi(struct portman *pm, 
			       int port, u8 mididata)
{
	int command = ((port + 4) << 1);

	/* Get entering data byte and port number in BL and BH respectively.
	 * Set up Tx Channel address field for use with PP Cmd Register.
	 * Store address field in BH register.
	 * Inputs:      AH = Output port number (0..3).
	 *              AL = Data byte.
	 *    command = TXDATA0 | INT_EN;
	 * Align port num with address field (b1...b3),
	 * set address for TXDatax, Strobe=0
	 */
	command |= INT_EN;

	/* Disable interrupts so that the process is not interrupted, then 
	 * write the address associated with the current Tx channel to the 
	 * PP Command Reg.  Do not set the Strobe signal yet.
	 */

	do {
		portman_write_command(pm, command);

		/* While the address lines settle, write parallel output data to 
		 * PP Data Reg.  This has no effect until Strobe signal is asserted.
		 */

		portman_write_data(pm, mididata);
		
		/* If PCP channel's TxEmpty is set (TxEmpty is read through the PP
		 * Status Register), then go write data.  Else go back and wait.
		 */
	} while ((portman_read_status(pm) & TXEMPTY) != TXEMPTY);

	/* TxEmpty is set.  Maintain PC/P destination address and assert
	 * Strobe through the PP Command Reg.  This will Strobe data into
	 * the PC/P transmitter and set the PC/P BUSY signal.
	 */

	portman_write_command(pm, command | STROBE);

	/* Wait for strobe line to settle and echo back through hardware.
	 * Once it has echoed back, assume that the address and data lines
	 * have settled!
	 */

	while ((portman_read_status(pm) & ESTB) == 0)
		cpu_relax();

	/* Release strobe and immediately re-allow interrupts. */
	portman_write_command(pm, command);

	while ((portman_read_status(pm) & ESTB) == ESTB)
		cpu_relax();

	/* PC/P BUSY is now set.  We must wait until BUSY resets itself.
	 * We'll reenable ints while we're waiting.
	 */

	while ((portman_read_status(pm) & BUSY) == BUSY)
		cpu_relax();

	/* Data sent. */
}