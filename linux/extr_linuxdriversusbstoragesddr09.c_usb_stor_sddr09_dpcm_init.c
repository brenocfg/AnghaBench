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
 int /*<<< orphan*/  USB_DIR_IN ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int sddr09_common_init (struct us_data*) ; 
 int sddr09_request_sense (struct us_data*,unsigned char*,int) ; 
 int sddr09_send_command (struct us_data*,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int
usb_stor_sddr09_dpcm_init(struct us_data *us) {
	int result;
	unsigned char *data = us->iobuf;

	result = sddr09_common_init(us);
	if (result)
		return result;

	result = sddr09_send_command(us, 0x01, USB_DIR_IN, data, 2);
	if (result) {
		usb_stor_dbg(us, "send_command fails\n");
		return result;
	}

	usb_stor_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 02

	result = sddr09_send_command(us, 0x08, USB_DIR_IN, data, 2);
	if (result) {
		usb_stor_dbg(us, "2nd send_command fails\n");
		return result;
	}

	usb_stor_dbg(us, "%02X %02X\n", data[0], data[1]);
	// get 07 00

	result = sddr09_request_sense(us, data, 18);
	if (result == 0 && data[2] != 0) {
		int j;
		for (j=0; j<18; j++)
			printk(" %02X", data[j]);
		printk("\n");
		// get 70 00 00 00 00 00 00 * 00 00 00 00 00 00
		// 70: current command
		// sense key 0, sense code 0, extd sense code 0
		// additional transfer length * = sizeof(data) - 7
		// Or: 70 00 06 00 00 00 00 0b 00 00 00 00 28 00 00 00 00 00
		// sense key 06, sense code 28: unit attention,
		// not ready to ready transition
	}

	// test unit ready

	return 0;		/* not result */
}