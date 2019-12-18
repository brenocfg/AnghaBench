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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t extractDataFromMask(uint16_t data, uint16_t mask) {
	int i, j;
	uint16_t result = 0;
	
	/* i counts through every bit of the data,
	 * j counts through every bit of the data we're copying out. */
	for (i = 0, j = 0; i < 16; i++) {
		/* If the mask has a bit in this position */
		if (mask & (1<<i)) {
			/* If there is a data bit with this mask bit,
			 * then toggle that bit in the extracted data (result).
			 * Notice that it uses its own bit counter j. */
			if (((mask & (1<<i)) & data) != 0)
				result |= (1<<j);
			/* Increment the extracted data bit count. */
			j++;
		}
	}
	
	return result;
}