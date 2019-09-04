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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct seeprom_config {int checksum; } ;

/* Variables and functions */

int
ahc_verify_cksum(struct seeprom_config *sc)
{
	int i;
	int maxaddr;
	uint32_t checksum;
	uint16_t *scarray;

	maxaddr = (sizeof(*sc)/2) - 1;
	checksum = 0;
	scarray = (uint16_t *)sc;

	for (i = 0; i < maxaddr; i++)
		checksum = checksum + scarray[i];
	if (checksum == 0
	 || (checksum & 0xFFFF) != sc->checksum) {
		return (0);
	} else {
		return(1);
	}
}