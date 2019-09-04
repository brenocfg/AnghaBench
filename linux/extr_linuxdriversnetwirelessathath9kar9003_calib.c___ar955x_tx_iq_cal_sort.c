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
struct coeff {int*** mag_coeff; int*** phs_coeff; } ;
struct ath_hw {int dummy; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALIBRATE ; 
 int MAXIQCAL ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static void __ar955x_tx_iq_cal_sort(struct ath_hw *ah,
				    struct coeff *coeff,
				    int i, int nmeasurement)
{
	struct ath_common *common = ath9k_hw_common(ah);
	int im, ix, iy, temp;

	for (im = 0; im < nmeasurement; im++) {
		for (ix = 0; ix < MAXIQCAL - 1; ix++) {
			for (iy = ix + 1; iy <= MAXIQCAL - 1; iy++) {
				if (coeff->mag_coeff[i][im][iy] <
				    coeff->mag_coeff[i][im][ix]) {
					temp = coeff->mag_coeff[i][im][ix];
					coeff->mag_coeff[i][im][ix] =
						coeff->mag_coeff[i][im][iy];
					coeff->mag_coeff[i][im][iy] = temp;
				}
				if (coeff->phs_coeff[i][im][iy] <
				    coeff->phs_coeff[i][im][ix]) {
					temp = coeff->phs_coeff[i][im][ix];
					coeff->phs_coeff[i][im][ix] =
						coeff->phs_coeff[i][im][iy];
					coeff->phs_coeff[i][im][iy] = temp;
				}
			}
		}
		coeff->mag_coeff[i][im][0] = coeff->mag_coeff[i][im][MAXIQCAL / 2];
		coeff->phs_coeff[i][im][0] = coeff->phs_coeff[i][im][MAXIQCAL / 2];

		ath_dbg(common, CALIBRATE,
			"IQCAL: Median [ch%d][gain%d]: mag = %d phase = %d\n",
			i, im,
			coeff->mag_coeff[i][im][0],
			coeff->phs_coeff[i][im][0]);
	}
}