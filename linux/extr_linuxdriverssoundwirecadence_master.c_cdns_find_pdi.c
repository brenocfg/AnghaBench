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
struct sdw_cdns_pdi {int assigned; } ;
struct sdw_cdns {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct sdw_cdns_pdi *cdns_find_pdi(struct sdw_cdns *cdns,
		unsigned int num, struct sdw_cdns_pdi *pdi)
{
	int i;

	for (i = 0; i < num; i++) {
		if (pdi[i].assigned == true)
			continue;
		pdi[i].assigned = true;
		return &pdi[i];
	}

	return NULL;
}