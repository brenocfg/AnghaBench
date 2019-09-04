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
typedef  int uint16_t ;

/* Variables and functions */
 int QLA_DSDS_PER_IOCB ; 

__attribute__((used)) static inline uint16_t
qla24xx_calc_dsd_lists(uint16_t dsds)
{
	uint16_t dsd_lists = 0;

	dsd_lists = (dsds/QLA_DSDS_PER_IOCB);
	if (dsds % QLA_DSDS_PER_IOCB)
		dsd_lists++;
	return dsd_lists;
}