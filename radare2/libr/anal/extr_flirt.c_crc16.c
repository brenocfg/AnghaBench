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
typedef  int ut8 ;
typedef  int ut32 ;
typedef  int /*<<< orphan*/  ut16 ;

/* Variables and functions */
 int POLY ; 

ut16 crc16(const unsigned char *data_p, size_t length) {
	ut8 i;
	ut32 data;
	ut32 crc = 0xFFFF;

	if (length == 0) {
		return 0;
	}
	do {
		data = *data_p++;
		for (i = 0; i < 8; i++) {
			if ((crc ^ data) & 1) {
				crc = (crc >> 1) ^ POLY;
			} else {
				crc >>= 1;
			}
			data >>= 1;
		}
	} while (--length > 0);

	crc = ~crc;
	data = crc;
	crc = (crc << 8) | ((data >> 8) & 0xff);
	return (ut16) (crc);
}