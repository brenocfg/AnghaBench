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
struct ad7280_state {int /*<<< orphan*/  crc_tab; } ;

/* Variables and functions */
 int EIO ; 
 unsigned char ad7280_calc_crc8 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad7280_check_crc(struct ad7280_state *st, unsigned int val)
{
	unsigned char crc = ad7280_calc_crc8(st->crc_tab, val >> 10);

	if (crc != ((val >> 2) & 0xFF))
		return -EIO;

	return 0;
}