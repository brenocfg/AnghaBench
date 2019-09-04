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

/* Variables and functions */
 int BMP_RLE_COMMAND ; 
 int BMP_RLE_TYPE_RAW ; 
 int BMP_RLE_TYPE_RLE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 

__attribute__((used)) static int build_rle_packet(unsigned char *row, int packet_type, int length, unsigned char *data)
{
	int compressed_size = 0;
	if (length < 1 || length > 128) {
		return 0;
	}

	/* Bitmap specific cases is that we can't have uncompressed rows of length 1 or 2 */
	if (packet_type == BMP_RLE_TYPE_RAW && length < 3) {
		int i = 0;
		for (i = 0; i < length; i++) {
			compressed_size += 2;
			memset(row, 1, 1);
			row++;

			memcpy(row, data++, 1);
			row++;
		}
	} else if (packet_type == BMP_RLE_TYPE_RLE) {
		compressed_size = 2;
		memset(row, length, 1);
		row++;

		memcpy(row, data, 1);
		row++;
	} else {
		compressed_size = 2 + length;
		memset(row, BMP_RLE_COMMAND, 1);
		row++;

		memset(row, length, 1);
		row++;

		memcpy(row, data, length);
		row += length;

		/* Must be an even number for an uncompressed run */
		if (length % 2) {
			memset(row, 0, 1);
			row++;
			compressed_size++;
		}
	}
	return compressed_size;
}