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
typedef  int u16 ;

/* Variables and functions */
 int crc_ccitt (int /*<<< orphan*/ ,int const*,size_t const) ; 
 int swab16 (int) ; 

__attribute__((used)) static bool rt2800_check_firmware_crc(const u8 *data, const size_t len)
{
	u16 fw_crc;
	u16 crc;

	/*
	 * The last 2 bytes in the firmware array are the crc checksum itself,
	 * this means that we should never pass those 2 bytes to the crc
	 * algorithm.
	 */
	fw_crc = (data[len - 2] << 8 | data[len - 1]);

	/*
	 * Use the crc ccitt algorithm.
	 * This will return the same value as the legacy driver which
	 * used bit ordering reversion on the both the firmware bytes
	 * before input input as well as on the final output.
	 * Obviously using crc ccitt directly is much more efficient.
	 */
	crc = crc_ccitt(~0, data, len - 2);

	/*
	 * There is a small difference between the crc-itu-t + bitrev and
	 * the crc-ccitt crc calculation. In the latter method the 2 bytes
	 * will be swapped, use swab16 to convert the crc to the correct
	 * value.
	 */
	crc = swab16(crc);

	return fw_crc == crc;
}