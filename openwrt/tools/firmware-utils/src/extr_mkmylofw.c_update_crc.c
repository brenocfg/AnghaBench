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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int* crc_32_tab ; 

void
update_crc(uint8_t *p, uint32_t len, uint32_t *crc)
{
	uint32_t t;

	t = *crc ^ 0xFFFFFFFFUL;
	while (len--) {
		t = crc_32_tab[(t ^ *p++) & 0xff] ^ (t >> 8);
	}
	*crc = t ^ 0xFFFFFFFFUL;
}