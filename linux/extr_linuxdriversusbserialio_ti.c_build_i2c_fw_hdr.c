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
struct ti_i2c_image_header {int /*<<< orphan*/  Length; } ;
struct ti_i2c_firmware_rec {int /*<<< orphan*/  Ver_Minor; int /*<<< orphan*/  Ver_Major; } ;
struct ti_i2c_desc {scalar_t__ CheckSum; int /*<<< orphan*/  Size; int /*<<< orphan*/  Type; scalar_t__ Data; } ;
struct firmware {int /*<<< orphan*/ * data; } ;
struct edgeport_fw_hdr {int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_DESC_TYPE_FIRMWARE_BLANK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 

__attribute__((used)) static int build_i2c_fw_hdr(u8 *header, const struct firmware *fw)
{
	__u8 *buffer;
	int buffer_size;
	int i;
	__u8 cs = 0;
	struct ti_i2c_desc *i2c_header;
	struct ti_i2c_image_header *img_header;
	struct ti_i2c_firmware_rec *firmware_rec;
	struct edgeport_fw_hdr *fw_hdr = (struct edgeport_fw_hdr *)fw->data;

	/*
	 * In order to update the I2C firmware we must change the type 2 record
	 * to type 0xF2.  This will force the UMP to come up in Boot Mode.
	 * Then while in boot mode, the driver will download the latest
	 * firmware (padded to 15.5k) into the UMP ram.  And finally when the
	 * device comes back up in download mode the driver will cause the new
	 * firmware to be copied from the UMP Ram to I2C and the firmware will
	 * update the record type from 0xf2 to 0x02.
	 */

	/*
	 * Allocate a 15.5k buffer + 2 bytes for version number (Firmware
	 * Record)
	 */
	buffer_size = (((1024 * 16) - 512 ) +
			sizeof(struct ti_i2c_firmware_rec));

	buffer = kmalloc(buffer_size, GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	/* Set entire image of 0xffs */
	memset(buffer, 0xff, buffer_size);

	/* Copy version number into firmware record */
	firmware_rec = (struct ti_i2c_firmware_rec *)buffer;

	firmware_rec->Ver_Major	= fw_hdr->major_version;
	firmware_rec->Ver_Minor	= fw_hdr->minor_version;

	/* Pointer to fw_down memory image */
	img_header = (struct ti_i2c_image_header *)&fw->data[4];

	memcpy(buffer + sizeof(struct ti_i2c_firmware_rec),
		&fw->data[4 + sizeof(struct ti_i2c_image_header)],
		le16_to_cpu(img_header->Length));

	for (i=0; i < buffer_size; i++) {
		cs = (__u8)(cs + buffer[i]);
	}

	kfree(buffer);

	/* Build new header */
	i2c_header =  (struct ti_i2c_desc *)header;
	firmware_rec =  (struct ti_i2c_firmware_rec*)i2c_header->Data;

	i2c_header->Type	= I2C_DESC_TYPE_FIRMWARE_BLANK;
	i2c_header->Size	= cpu_to_le16(buffer_size);
	i2c_header->CheckSum	= cs;
	firmware_rec->Ver_Major	= fw_hdr->major_version;
	firmware_rec->Ver_Minor	= fw_hdr->minor_version;

	return 0;
}