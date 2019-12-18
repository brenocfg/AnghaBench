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
struct c2c_stats {scalar_t__ st_l1miss; scalar_t__ st_l1hit; scalar_t__ lcl_hitm; scalar_t__ ld_llchit; scalar_t__ ld_l2hit; scalar_t__ ld_l1hit; scalar_t__ ld_fbhit; scalar_t__ rmt_hit; scalar_t__ rmt_hitm; scalar_t__ rmt_dram; scalar_t__ lcl_dram; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t total_records(struct c2c_stats *stats)
{
	uint64_t lclmiss, ldcnt, total;

	lclmiss  = stats->lcl_dram +
		   stats->rmt_dram +
		   stats->rmt_hitm +
		   stats->rmt_hit;

	ldcnt    = lclmiss +
		   stats->ld_fbhit +
		   stats->ld_l1hit +
		   stats->ld_l2hit +
		   stats->ld_llchit +
		   stats->lcl_hitm;

	total    = ldcnt +
		   stats->st_l1hit +
		   stats->st_l1miss;

	return total;
}