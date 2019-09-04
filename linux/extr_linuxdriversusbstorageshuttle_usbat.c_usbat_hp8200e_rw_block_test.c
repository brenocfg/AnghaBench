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
struct us_data {unsigned int recv_bulk_pipe; unsigned int send_bulk_pipe; unsigned char* iobuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 unsigned char LSB_of (unsigned short) ; 
 unsigned char MSB_of (unsigned short) ; 
 int /*<<< orphan*/  USBAT_ATA ; 
 int /*<<< orphan*/  USBAT_ATA_ALTSTATUS ; 
 int /*<<< orphan*/  USBAT_ATA_STATUS ; 
 unsigned char USBAT_CMD_COND_READ_BLOCK ; 
 unsigned char USBAT_CMD_COND_WRITE_BLOCK ; 
 unsigned char USBAT_CMD_WRITE_REGS ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_FAILED ; 
 int USB_STOR_XFER_GOOD ; 
 int USB_STOR_XFER_SHORT ; 
 int USB_STOR_XFER_STALLED ; 
 int US_IOBUF_SIZE ; 
 int usb_stor_bulk_transfer_sg (struct us_data*,unsigned int,void*,unsigned short,int,int /*<<< orphan*/ *) ; 
 scalar_t__ usb_stor_clear_halt (struct us_data*,unsigned int) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,char*) ; 
 int usbat_bulk_write (struct us_data*,unsigned char*,unsigned short,int /*<<< orphan*/ ) ; 
 int usbat_execute_command (struct us_data*,unsigned char*,int) ; 
 int usbat_read (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int usbat_wait_not_busy (struct us_data*,int) ; 

__attribute__((used)) static int usbat_hp8200e_rw_block_test(struct us_data *us,
				       unsigned char access,
				       unsigned char *registers,
				       unsigned char *data_out,
				       unsigned short num_registers,
				       unsigned char data_reg,
				       unsigned char status_reg,
				       unsigned char timeout,
				       unsigned char qualifier,
				       int direction,
				       void *buf,
				       unsigned short len,
				       int use_sg,
				       int minutes)
{
	int result;
	unsigned int pipe = (direction == DMA_FROM_DEVICE) ?
			us->recv_bulk_pipe : us->send_bulk_pipe;

	unsigned char *command = us->iobuf;
	int i, j;
	int cmdlen;
	unsigned char *data = us->iobuf;
	unsigned char *status = us->iobuf;

	BUG_ON(num_registers > US_IOBUF_SIZE/2);

	for (i=0; i<20; i++) {

		/*
		 * The first time we send the full command, which consists
		 * of downloading the SCSI command followed by downloading
		 * the data via a write-and-test.  Any other time we only
		 * send the command to download the data -- the SCSI command
		 * is still 'active' in some sense in the device.
		 * 
		 * We're only going to try sending the data 10 times. After
		 * that, we just return a failure.
		 */

		if (i==0) {
			cmdlen = 16;
			/*
			 * Write to multiple registers
			 * Not really sure the 0x07, 0x17, 0xfc, 0xe7 is
			 * necessary here, but that's what came out of the
			 * trace every single time.
			 */
			command[0] = 0x40;
			command[1] = access | USBAT_CMD_WRITE_REGS;
			command[2] = 0x07;
			command[3] = 0x17;
			command[4] = 0xFC;
			command[5] = 0xE7;
			command[6] = LSB_of(num_registers*2);
			command[7] = MSB_of(num_registers*2);
		} else
			cmdlen = 8;

		/* Conditionally read or write blocks */
		command[cmdlen-8] = (direction==DMA_TO_DEVICE ? 0x40 : 0xC0);
		command[cmdlen-7] = access |
				(direction==DMA_TO_DEVICE ?
				 USBAT_CMD_COND_WRITE_BLOCK : USBAT_CMD_COND_READ_BLOCK);
		command[cmdlen-6] = data_reg;
		command[cmdlen-5] = status_reg;
		command[cmdlen-4] = timeout;
		command[cmdlen-3] = qualifier;
		command[cmdlen-2] = LSB_of(len);
		command[cmdlen-1] = MSB_of(len);

		result = usbat_execute_command(us, command, cmdlen);

		if (result != USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;

		if (i==0) {

			for (j=0; j<num_registers; j++) {
				data[j<<1] = registers[j];
				data[1+(j<<1)] = data_out[j];
			}

			result = usbat_bulk_write(us, data, num_registers*2, 0);
			if (result != USB_STOR_XFER_GOOD)
				return USB_STOR_TRANSPORT_ERROR;

		}

		result = usb_stor_bulk_transfer_sg(us,
			pipe, buf, len, use_sg, NULL);

		/*
		 * If we get a stall on the bulk download, we'll retry
		 * the bulk download -- but not the SCSI command because
		 * in some sense the SCSI command is still 'active' and
		 * waiting for the data. Don't ask me why this should be;
		 * I'm only following what the Windoze driver did.
		 *
		 * Note that a stall for the test-and-read/write command means
		 * that the test failed. In this case we're testing to make
		 * sure that the device is error-free
		 * (i.e. bit 0 -- CHK -- of status is 0). The most likely
		 * hypothesis is that the USBAT chip somehow knows what
		 * the device will accept, but doesn't give the device any
		 * data until all data is received. Thus, the device would
		 * still be waiting for the first byte of data if a stall
		 * occurs, even if the stall implies that some data was
		 * transferred.
		 */

		if (result == USB_STOR_XFER_SHORT ||
				result == USB_STOR_XFER_STALLED) {

			/*
			 * If we're reading and we stalled, then clear
			 * the bulk output pipe only the first time.
			 */

			if (direction==DMA_FROM_DEVICE && i==0) {
				if (usb_stor_clear_halt(us,
						us->send_bulk_pipe) < 0)
					return USB_STOR_TRANSPORT_ERROR;
			}

			/*
			 * Read status: is the device angry, or just busy?
			 */

 			result = usbat_read(us, USBAT_ATA, 
				direction==DMA_TO_DEVICE ?
					USBAT_ATA_STATUS : USBAT_ATA_ALTSTATUS,
				status);

			if (result!=USB_STOR_XFER_GOOD)
				return USB_STOR_TRANSPORT_ERROR;
			if (*status & 0x01) /* check condition */
				return USB_STOR_TRANSPORT_FAILED;
			if (*status & 0x20) /* device fault */
				return USB_STOR_TRANSPORT_FAILED;

			usb_stor_dbg(us, "Redoing %s\n",
				     direction == DMA_TO_DEVICE
				     ? "write" : "read");

		} else if (result != USB_STOR_XFER_GOOD)
			return USB_STOR_TRANSPORT_ERROR;
		else
			return usbat_wait_not_busy(us, minutes);

	}

	usb_stor_dbg(us, "Bummer! %s bulk data 20 times failed\n",
		     direction == DMA_TO_DEVICE ? "Writing" : "Reading");

	return USB_STOR_TRANSPORT_FAILED;
}