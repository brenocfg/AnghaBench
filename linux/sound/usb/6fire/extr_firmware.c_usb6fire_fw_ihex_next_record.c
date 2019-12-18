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
typedef  int u8 ;
struct ihex_record {int error; int txt_offset; int txt_length; char* txt_data; int len; int address; int* data; } ;

/* Variables and functions */
 int usb6fire_fw_ihex_hex (char*,int*) ; 

__attribute__((used)) static bool usb6fire_fw_ihex_next_record(struct ihex_record *record)
{
	u8 crc = 0;
	u8 type;
	int i;

	record->error = false;

	/* find begin of record (marked by a colon) */
	while (record->txt_offset < record->txt_length
			&& record->txt_data[record->txt_offset] != ':')
		record->txt_offset++;
	if (record->txt_offset == record->txt_length)
		return false;

	/* number of characters needed for len, addr and type entries */
	record->txt_offset++;
	if (record->txt_offset + 8 > record->txt_length) {
		record->error = true;
		return false;
	}

	record->len = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;
	record->address = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc) << 8;
	record->txt_offset += 2;
	record->address |= usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;
	type = usb6fire_fw_ihex_hex(record->txt_data +
			record->txt_offset, &crc);
	record->txt_offset += 2;

	/* number of characters needed for data and crc entries */
	if (record->txt_offset + 2 * (record->len + 1) > record->txt_length) {
		record->error = true;
		return false;
	}
	for (i = 0; i < record->len; i++) {
		record->data[i] = usb6fire_fw_ihex_hex(record->txt_data
				+ record->txt_offset, &crc);
		record->txt_offset += 2;
	}
	usb6fire_fw_ihex_hex(record->txt_data + record->txt_offset, &crc);
	if (crc) {
		record->error = true;
		return false;
	}

	if (type == 1 || !record->len) /* eof */
		return false;
	else if (type == 0)
		return true;
	else {
		record->error = true;
		return false;
	}
}