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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static void fsl_spi_grlib_set_shifts(u32 *rx_shift, u32 *tx_shift,
				     int bits_per_word, int msb_first)
{
	*rx_shift = 0;
	*tx_shift = 0;
	if (bits_per_word <= 16) {
		if (msb_first) {
			*rx_shift = 16; /* LSB in bit 16 */
			*tx_shift = 32 - bits_per_word; /* MSB in bit 31 */
		} else {
			*rx_shift = 16 - bits_per_word; /* MSB in bit 15 */
		}
	}
}