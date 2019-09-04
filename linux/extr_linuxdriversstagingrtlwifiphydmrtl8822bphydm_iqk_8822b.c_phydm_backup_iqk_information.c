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
struct dm_iqk_info {int** rxiqk_agc; int** rxiqk_fail_code; int*** iqk_fail_report; int*** gs_retry_count; int*** retry_count; int /*<<< orphan*/ **** iqk_cfir_imag; int /*<<< orphan*/ **** iqk_cfir_real; int /*<<< orphan*/ ** bypass_iqk; int /*<<< orphan*/ ** lok_idac; int /*<<< orphan*/ * iqk_channel; } ;

/* Variables and functions */

__attribute__((used)) static inline void phydm_backup_iqk_information(struct dm_iqk_info *iqk_info)
{
	u8 i, j, k;

	iqk_info->iqk_channel[1] = iqk_info->iqk_channel[0];
	for (i = 0; i < 2; i++) {
		iqk_info->lok_idac[1][i] = iqk_info->lok_idac[0][i];
		iqk_info->rxiqk_agc[1][i] = iqk_info->rxiqk_agc[0][i];
		iqk_info->bypass_iqk[1][i] = iqk_info->bypass_iqk[0][i];
		iqk_info->rxiqk_fail_code[1][i] =
			iqk_info->rxiqk_fail_code[0][i];
		for (j = 0; j < 2; j++) {
			iqk_info->iqk_fail_report[1][i][j] =
				iqk_info->iqk_fail_report[0][i][j];
			for (k = 0; k < 8; k++) {
				iqk_info->iqk_cfir_real[1][i][j][k] =
					iqk_info->iqk_cfir_real[0][i][j][k];
				iqk_info->iqk_cfir_imag[1][i][j][k] =
					iqk_info->iqk_cfir_imag[0][i][j][k];
			}
		}
	}

	for (i = 0; i < 4; i++) {
		iqk_info->rxiqk_fail_code[0][i] = 0x0;
		iqk_info->rxiqk_agc[0][i] = 0x0;
		for (j = 0; j < 2; j++) {
			iqk_info->iqk_fail_report[0][i][j] = true;
			iqk_info->gs_retry_count[0][i][j] = 0x0;
		}
		for (j = 0; j < 3; j++)
			iqk_info->retry_count[0][i][j] = 0x0;
	}
}