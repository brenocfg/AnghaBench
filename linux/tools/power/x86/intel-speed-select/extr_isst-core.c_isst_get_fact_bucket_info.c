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
struct isst_fact_bucket_info {unsigned int high_priority_cores_count; unsigned int sse_trl; unsigned int avx_trl; unsigned int avx512_trl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TDP ; 
 int /*<<< orphan*/  CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES ; 
 int /*<<< orphan*/  CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS ; 
 int /*<<< orphan*/  debug_printf (char*,int,int,int,int,...) ; 
 int isst_send_mbox_command (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int*) ; 

int isst_get_fact_bucket_info(int cpu, int level,
			      struct isst_fact_bucket_info *bucket_info)
{
	unsigned int resp;
	int i, k, ret;

	for (i = 0; i < 2; ++i) {
		int j;

		ret = isst_send_mbox_command(
			cpu, CONFIG_TDP,
			CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES, 0,
			(i << 8) | level, &resp);
		if (ret)
			return ret;

		debug_printf(
			"cpu:%d CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_NUMCORES index:%d level:%d resp:%x\n",
			cpu, i, level, resp);

		for (j = 0; j < 4; ++j) {
			bucket_info[j + (i * 4)].high_priority_cores_count =
				(resp >> (j * 8)) & 0xff;
		}
	}

	for (k = 0; k < 3; ++k) {
		for (i = 0; i < 2; ++i) {
			int j;

			ret = isst_send_mbox_command(
				cpu, CONFIG_TDP,
				CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS, 0,
				(k << 16) | (i << 8) | level, &resp);
			if (ret)
				return ret;

			debug_printf(
				"cpu:%d CONFIG_TDP_GET_FACT_HP_TURBO_LIMIT_RATIOS index:%d level:%d avx:%d resp:%x\n",
				cpu, i, level, k, resp);

			for (j = 0; j < 4; ++j) {
				switch (k) {
				case 0:
					bucket_info[j + (i * 4)].sse_trl =
						(resp >> (j * 8)) & 0xff;
					break;
				case 1:
					bucket_info[j + (i * 4)].avx_trl =
						(resp >> (j * 8)) & 0xff;
					break;
				case 2:
					bucket_info[j + (i * 4)].avx512_trl =
						(resp >> (j * 8)) & 0xff;
					break;
				default:
					break;
				}
			}
		}
	}

	return 0;
}