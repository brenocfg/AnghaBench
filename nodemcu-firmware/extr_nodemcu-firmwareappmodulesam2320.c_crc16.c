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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t crc16(uint8_t *ptr, unsigned int len)
{
    uint16_t	crc =0xFFFF;
    uint8_t	i;

    while(len--) {
	crc ^= *ptr++;
	for(i=0;i<8;i++) {
	    if(crc & 0x01) {
		crc >>= 1;
		crc ^= 0xA001;
	    } else {
		crc >>= 1;
	    }
	}
    }
    return crc;
}