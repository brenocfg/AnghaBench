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
typedef  scalar_t__ u32 ;

/* Variables and functions */

void phydm_seq_sorting(void *dm_void, u32 *value, u32 *rank_idx, u32 *idx_out,
		       u8 seq_length)
{
	u8 i = 0, j = 0;
	u32 tmp_a, tmp_b;
	u32 tmp_idx_a, tmp_idx_b;

	for (i = 0; i < seq_length; i++) {
		rank_idx[i] = i;
		/**/
	}

	for (i = 0; i < (seq_length - 1); i++) {
		for (j = 0; j < (seq_length - 1 - i); j++) {
			tmp_a = value[j];
			tmp_b = value[j + 1];

			tmp_idx_a = rank_idx[j];
			tmp_idx_b = rank_idx[j + 1];

			if (tmp_a < tmp_b) {
				value[j] = tmp_b;
				value[j + 1] = tmp_a;

				rank_idx[j] = tmp_idx_b;
				rank_idx[j + 1] = tmp_idx_a;
			}
		}
	}

	for (i = 0; i < seq_length; i++) {
		idx_out[rank_idx[i]] = i + 1;
		/**/
	}
}