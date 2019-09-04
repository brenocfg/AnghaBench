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
struct ad7746_chip_info {int config; } ;

/* Variables and functions */
 int AD7746_CONF_VTFS_MASK ; 
 int AD7746_CONF_VTFS_SHIFT ; 
 int ARRAY_SIZE (int**) ; 
 int** ad7746_vt_filter_rate_table ; 

__attribute__((used)) static int ad7746_store_vt_filter_rate_setup(struct ad7746_chip_info *chip,
					     int val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ad7746_vt_filter_rate_table); i++)
		if (val >= ad7746_vt_filter_rate_table[i][0])
			break;

	if (i >= ARRAY_SIZE(ad7746_vt_filter_rate_table))
		i = ARRAY_SIZE(ad7746_vt_filter_rate_table) - 1;

	chip->config &= ~AD7746_CONF_VTFS_MASK;
	chip->config |= i << AD7746_CONF_VTFS_SHIFT;

	return 0;
}