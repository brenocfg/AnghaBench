#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union perf_mem_data_src {int mem_op; int mem_lvl; int mem_snoop; int mem_lock; int mem_remote; } ;
typedef  int u64 ;
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
struct TYPE_3__ {int addr; int /*<<< orphan*/  map; } ;
struct mem_info {TYPE_2__ iaddr; TYPE_1__ daddr; union perf_mem_data_src data_src; } ;
struct c2c_stats {int /*<<< orphan*/  nomap; int /*<<< orphan*/  noparse; int /*<<< orphan*/  st_l1miss; int /*<<< orphan*/  st_l1hit; int /*<<< orphan*/  st_uncache; int /*<<< orphan*/  st_noadrs; int /*<<< orphan*/  store; int /*<<< orphan*/  ld_miss; int /*<<< orphan*/  tot_hitm; int /*<<< orphan*/  rmt_hitm; int /*<<< orphan*/  rmt_hit; int /*<<< orphan*/  ld_excl; int /*<<< orphan*/  ld_shared; int /*<<< orphan*/  rmt_dram; int /*<<< orphan*/  lcl_dram; int /*<<< orphan*/  ld_llchit; int /*<<< orphan*/  lcl_hitm; int /*<<< orphan*/  ld_l2hit; int /*<<< orphan*/  ld_l1hit; int /*<<< orphan*/  ld_fbhit; int /*<<< orphan*/  ld_io; int /*<<< orphan*/  ld_uncache; int /*<<< orphan*/  ld_noadrs; int /*<<< orphan*/  load; int /*<<< orphan*/  locks; int /*<<< orphan*/  nr_entries; } ;

/* Variables and functions */
 int PERF_MEM_LOCK_LOCKED ; 
 int PERF_MEM_LVL_HIT ; 
 int PERF_MEM_LVL_IO ; 
 int PERF_MEM_LVL_L1 ; 
 int PERF_MEM_LVL_L2 ; 
 int PERF_MEM_LVL_L3 ; 
 int PERF_MEM_LVL_LFB ; 
 int PERF_MEM_LVL_LOC_RAM ; 
 int PERF_MEM_LVL_MISS ; 
 int PERF_MEM_LVL_REM_CCE1 ; 
 int PERF_MEM_LVL_REM_CCE2 ; 
 int PERF_MEM_LVL_REM_RAM1 ; 
 int PERF_MEM_LVL_REM_RAM2 ; 
 int PERF_MEM_LVL_UNC ; 
 int PERF_MEM_OP_LOAD ; 
 int PERF_MEM_OP_STORE ; 
 int PERF_MEM_SNOOP_HIT ; 
 int PERF_MEM_SNOOP_HITM ; 

int c2c_decode_stats(struct c2c_stats *stats, struct mem_info *mi)
{
	union perf_mem_data_src *data_src = &mi->data_src;
	u64 daddr  = mi->daddr.addr;
	u64 op     = data_src->mem_op;
	u64 lvl    = data_src->mem_lvl;
	u64 snoop  = data_src->mem_snoop;
	u64 lock   = data_src->mem_lock;
	/*
	 * Skylake might report unknown remote level via this
	 * bit, consider it when evaluating remote HITMs.
	 */
	bool mrem  = data_src->mem_remote;
	int err = 0;

#define HITM_INC(__f)		\
do {				\
	stats->__f++;		\
	stats->tot_hitm++;	\
} while (0)

#define P(a, b) PERF_MEM_##a##_##b

	stats->nr_entries++;

	if (lock & P(LOCK, LOCKED)) stats->locks++;

	if (op & P(OP, LOAD)) {
		/* load */
		stats->load++;

		if (!daddr) {
			stats->ld_noadrs++;
			return -1;
		}

		if (lvl & P(LVL, HIT)) {
			if (lvl & P(LVL, UNC)) stats->ld_uncache++;
			if (lvl & P(LVL, IO))  stats->ld_io++;
			if (lvl & P(LVL, LFB)) stats->ld_fbhit++;
			if (lvl & P(LVL, L1 )) stats->ld_l1hit++;
			if (lvl & P(LVL, L2 )) stats->ld_l2hit++;
			if (lvl & P(LVL, L3 )) {
				if (snoop & P(SNOOP, HITM))
					HITM_INC(lcl_hitm);
				else
					stats->ld_llchit++;
			}

			if (lvl & P(LVL, LOC_RAM)) {
				stats->lcl_dram++;
				if (snoop & P(SNOOP, HIT))
					stats->ld_shared++;
				else
					stats->ld_excl++;
			}

			if ((lvl & P(LVL, REM_RAM1)) ||
			    (lvl & P(LVL, REM_RAM2)) ||
			     mrem) {
				stats->rmt_dram++;
				if (snoop & P(SNOOP, HIT))
					stats->ld_shared++;
				else
					stats->ld_excl++;
			}
		}

		if ((lvl & P(LVL, REM_CCE1)) ||
		    (lvl & P(LVL, REM_CCE2)) ||
		     mrem) {
			if (snoop & P(SNOOP, HIT))
				stats->rmt_hit++;
			else if (snoop & P(SNOOP, HITM))
				HITM_INC(rmt_hitm);
		}

		if ((lvl & P(LVL, MISS)))
			stats->ld_miss++;

	} else if (op & P(OP, STORE)) {
		/* store */
		stats->store++;

		if (!daddr) {
			stats->st_noadrs++;
			return -1;
		}

		if (lvl & P(LVL, HIT)) {
			if (lvl & P(LVL, UNC)) stats->st_uncache++;
			if (lvl & P(LVL, L1 )) stats->st_l1hit++;
		}
		if (lvl & P(LVL, MISS))
			if (lvl & P(LVL, L1)) stats->st_l1miss++;
	} else {
		/* unparsable data_src? */
		stats->noparse++;
		return -1;
	}

	if (!mi->daddr.map || !mi->iaddr.map) {
		stats->nomap++;
		return -1;
	}

#undef P
#undef HITM_INC
	return err;
}