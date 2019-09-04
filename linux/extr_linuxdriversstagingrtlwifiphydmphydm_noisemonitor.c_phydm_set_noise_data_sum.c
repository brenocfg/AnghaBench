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
typedef  size_t u8 ;
struct noise_level {int* valid_cnt; int* sum; } ;

/* Variables and functions */
 size_t ODM_RF_PATH_A ; 

__attribute__((used)) static inline void phydm_set_noise_data_sum(struct noise_level *noise_data,
					    u8 max_rf_path)
{
	u8 rf_path;

	for (rf_path = ODM_RF_PATH_A; rf_path < max_rf_path; rf_path++) {
		if (noise_data->valid_cnt[rf_path])
			noise_data->sum[rf_path] /=
				noise_data->valid_cnt[rf_path];
		else
			noise_data->sum[rf_path] = 0;
	}
}