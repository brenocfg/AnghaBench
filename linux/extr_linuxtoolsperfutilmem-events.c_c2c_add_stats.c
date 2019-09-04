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
struct c2c_stats {scalar_t__ noparse; scalar_t__ nomap; scalar_t__ rmt_dram; scalar_t__ lcl_dram; scalar_t__ rmt_hit; scalar_t__ tot_hitm; scalar_t__ rmt_hitm; scalar_t__ lcl_hitm; scalar_t__ ld_llchit; scalar_t__ ld_l2hit; scalar_t__ ld_l1hit; scalar_t__ ld_fbhit; scalar_t__ ld_noadrs; scalar_t__ ld_miss; scalar_t__ ld_io; scalar_t__ ld_uncache; scalar_t__ ld_shared; scalar_t__ ld_excl; scalar_t__ load; scalar_t__ st_l1miss; scalar_t__ st_l1hit; scalar_t__ st_noadrs; scalar_t__ st_uncache; scalar_t__ store; scalar_t__ locks; scalar_t__ nr_entries; } ;

/* Variables and functions */

void c2c_add_stats(struct c2c_stats *stats, struct c2c_stats *add)
{
	stats->nr_entries	+= add->nr_entries;

	stats->locks		+= add->locks;
	stats->store		+= add->store;
	stats->st_uncache	+= add->st_uncache;
	stats->st_noadrs	+= add->st_noadrs;
	stats->st_l1hit		+= add->st_l1hit;
	stats->st_l1miss	+= add->st_l1miss;
	stats->load		+= add->load;
	stats->ld_excl		+= add->ld_excl;
	stats->ld_shared	+= add->ld_shared;
	stats->ld_uncache	+= add->ld_uncache;
	stats->ld_io		+= add->ld_io;
	stats->ld_miss		+= add->ld_miss;
	stats->ld_noadrs	+= add->ld_noadrs;
	stats->ld_fbhit		+= add->ld_fbhit;
	stats->ld_l1hit		+= add->ld_l1hit;
	stats->ld_l2hit		+= add->ld_l2hit;
	stats->ld_llchit	+= add->ld_llchit;
	stats->lcl_hitm		+= add->lcl_hitm;
	stats->rmt_hitm		+= add->rmt_hitm;
	stats->tot_hitm		+= add->tot_hitm;
	stats->rmt_hit		+= add->rmt_hit;
	stats->lcl_dram		+= add->lcl_dram;
	stats->rmt_dram		+= add->rmt_dram;
	stats->nomap		+= add->nomap;
	stats->noparse		+= add->noparse;
}