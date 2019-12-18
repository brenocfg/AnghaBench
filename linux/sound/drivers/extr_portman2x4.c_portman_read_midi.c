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
struct portman {int dummy; } ;

/* Variables and functions */
 int ESTB ; 
 int INT_EN ; 
 int RXAVAIL ; 
 unsigned char STROBE ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int portman_read_status (struct portman*) ; 
 int /*<<< orphan*/  portman_write_command (struct portman*,unsigned char) ; 
 int /*<<< orphan*/  portman_write_data (struct portman*,int) ; 

__attribute__((used)) static int portman_read_midi(struct portman *pm, int port)
{
	unsigned char midi_data = 0;
	unsigned char cmdout;	/* Saved address+IE bit. */

	/* Make sure clocking edge is down before starting... */
	portman_write_data(pm, 0);	/* Make sure edge is down. */

	/* Set destination address to PCP. */
	cmdout = (port << 1) | INT_EN;	/* Address + IE + No Strobe. */
	portman_write_command(pm, cmdout);

	while ((portman_read_status(pm) & ESTB) == ESTB)
		cpu_relax();	/* Wait for strobe echo. */

	/* After the address lines settle, check multiplexed RxAvail signal.
	 * If data is available, read it.
	 */
	if ((portman_read_status(pm) & RXAVAIL) == 0)
		return -1;	/* No data. */

	/* Set the Strobe signal to enable the Rx clocking circuitry. */
	portman_write_command(pm, cmdout | STROBE);	/* Write address+IE+Strobe. */

	while ((portman_read_status(pm) & ESTB) == 0)
		cpu_relax(); /* Wait for strobe echo. */

	/* The first data bit (msb) is already sitting on the input line. */
	midi_data = (portman_read_status(pm) & 128);
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 6. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 1) & 64;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 5. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 2) & 32;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 4. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 3) & 16;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 3. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 4) & 8;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 2. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 5) & 4;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 1. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 6) & 2;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */

	/* Data bit 0. */
	portman_write_data(pm, 0);	/* Cause falling edge while data settles. */
	midi_data |= (portman_read_status(pm) >> 7) & 1;
	portman_write_data(pm, 1);	/* Cause rising edge, which shifts data. */
	portman_write_data(pm, 0);	/* Return data clock low. */


	/* De-assert Strobe and return data. */
	portman_write_command(pm, cmdout);	/* Output saved address+IE. */

	/* Wait for strobe echo. */
	while ((portman_read_status(pm) & ESTB) == ESTB)
		cpu_relax();

	return (midi_data & 255);	/* Shift back and return value. */
}