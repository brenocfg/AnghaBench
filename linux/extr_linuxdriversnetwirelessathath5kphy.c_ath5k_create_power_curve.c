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
typedef  int s16 ;

/* Variables and functions */
 int AR5K_EEPROM_POWER_TABLE_SIZE ; 
 int AR5K_PWRTABLE_LINEAR_PCDAC ; 
 scalar_t__ ath5k_get_interpolated_value (int,int const,int const,int const,int const) ; 

__attribute__((used)) static void
ath5k_create_power_curve(s16 pmin, s16 pmax,
			const s16 *pwr, const u8 *vpd,
			u8 num_points,
			u8 *vpd_table, u8 type)
{
	u8 idx[2] = { 0, 1 };
	s16 pwr_i = 2 * pmin;
	int i;

	if (num_points < 2)
		return;

	/* We want the whole line, so adjust boundaries
	 * to cover the entire power range. Note that
	 * power values are already 0.25dB so no need
	 * to multiply pwr_i by 2 */
	if (type == AR5K_PWRTABLE_LINEAR_PCDAC) {
		pwr_i = pmin;
		pmin = 0;
		pmax = 63;
	}

	/* Find surrounding turning points (TPs)
	 * and interpolate between them */
	for (i = 0; (i <= (u16) (pmax - pmin)) &&
	(i < AR5K_EEPROM_POWER_TABLE_SIZE); i++) {

		/* We passed the right TP, move to the next set of TPs
		 * if we pass the last TP, extrapolate above using the last
		 * two TPs for ratio */
		if ((pwr_i > pwr[idx[1]]) && (idx[1] < num_points - 1)) {
			idx[0]++;
			idx[1]++;
		}

		vpd_table[i] = (u8) ath5k_get_interpolated_value(pwr_i,
						pwr[idx[0]], pwr[idx[1]],
						vpd[idx[0]], vpd[idx[1]]);

		/* Increase by 0.5dB
		 * (0.25 dB units) */
		pwr_i += 2;
	}
}