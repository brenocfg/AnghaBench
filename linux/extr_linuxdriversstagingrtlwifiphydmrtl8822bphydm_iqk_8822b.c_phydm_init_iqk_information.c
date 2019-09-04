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
struct dm_iqk_info {int* iqk_channel; int** lok_idac; int** rxiqk_agc; int** bypass_iqk; int*** iqk_fail_report; int**** iqk_cfir_real; int**** iqk_cfir_imag; int*** retry_count; } ;

/* Variables and functions */
 int SS_8822B ; 

__attribute__((used)) static inline void phydm_init_iqk_information(struct dm_iqk_info *iqk_info)
{
	u8 i, j, k, m;

	for (i = 0; i < 2; i++) {
		iqk_info->iqk_channel[i] = 0x0;

		for (j = 0; j < SS_8822B; j++) {
			iqk_info->lok_idac[i][j] = 0x0;
			iqk_info->rxiqk_agc[i][j] = 0x0;
			iqk_info->bypass_iqk[i][j] = 0x0;

			for (k = 0; k < 2; k++) {
				iqk_info->iqk_fail_report[i][j][k] = true;
				for (m = 0; m < 8; m++) {
					iqk_info->iqk_cfir_real[i][j][k][m] =
						0x0;
					iqk_info->iqk_cfir_imag[i][j][k][m] =
						0x0;
				}
			}

			for (k = 0; k < 3; k++)
				iqk_info->retry_count[i][j][k] = 0x0;
		}
	}
}