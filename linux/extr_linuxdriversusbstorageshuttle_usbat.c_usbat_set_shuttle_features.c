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
struct us_data {unsigned char* iobuf; } ;

/* Variables and functions */
 unsigned char USBAT_CMD_SET_FEAT ; 
 int usbat_execute_command (struct us_data*,unsigned char*,int) ; 

__attribute__((used)) static int usbat_set_shuttle_features(struct us_data *us,
				      unsigned char external_trigger,
				      unsigned char epp_control,
				      unsigned char mask_byte,
				      unsigned char test_pattern,
				      unsigned char subcountH,
				      unsigned char subcountL)
{
	unsigned char *command = us->iobuf;

	command[0] = 0x40;
	command[1] = USBAT_CMD_SET_FEAT;

	/*
	 * The only bit relevant to ATA access is bit 6
	 * which defines 8 bit data access (set) or 16 bit (unset)
	 */
	command[2] = epp_control;

	/*
	 * If FCQ is set in the qualifier (defined in R/W cmd), then bits U0, U1,
	 * ET1 and ET2 define an external event to be checked for on event of a
	 * _read_blocks or _write_blocks operation. The read/write will not take
	 * place unless the defined trigger signal is active.
	 */
	command[3] = external_trigger;

	/*
	 * The resultant byte of the mask operation (see mask_byte) is compared for
	 * equivalence with this test pattern. If equal, the read/write will take
	 * place.
	 */
	command[4] = test_pattern;

	/*
	 * This value is logically ANDed with the status register field specified
	 * in the read/write command.
	 */
	command[5] = mask_byte;

	/*
	 * If ALQ is set in the qualifier, this field contains the address of the
	 * registers where the byte count should be read for transferring the data.
	 * If ALQ is not set, then this field contains the number of bytes to be
	 * transferred.
	 */
	command[6] = subcountL;
	command[7] = subcountH;

	return usbat_execute_command(us, command, 8);
}