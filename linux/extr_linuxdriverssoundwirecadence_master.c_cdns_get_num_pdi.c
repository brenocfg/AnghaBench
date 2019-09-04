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
typedef  scalar_t__ u32 ;
struct sdw_cdns_pdi {int assigned; scalar_t__ ch_count; } ;
struct sdw_cdns {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int cdns_get_num_pdi(struct sdw_cdns *cdns,
		struct sdw_cdns_pdi *pdi,
		unsigned int num, u32 ch_count)
{
	int i, pdis = 0;

	for (i = 0; i < num; i++) {
		if (pdi[i].assigned == true)
			continue;

		if (pdi[i].ch_count < ch_count)
			ch_count -= pdi[i].ch_count;
		else
			ch_count = 0;

		pdis++;

		if (!ch_count)
			break;
	}

	if (ch_count)
		return 0;

	return pdis;
}