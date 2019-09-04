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
typedef  scalar_t__ uint64_t ;
struct c2c_stats {scalar_t__ rmt_hit; scalar_t__ rmt_hitm; scalar_t__ rmt_dram; scalar_t__ lcl_dram; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t llc_miss(struct c2c_stats *stats)
{
	uint64_t llcmiss;

	llcmiss = stats->lcl_dram +
		  stats->rmt_dram +
		  stats->rmt_hitm +
		  stats->rmt_hit;

	return llcmiss;
}