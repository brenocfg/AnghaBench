#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snic_misc_stats {int /*<<< orphan*/  max_cq_ents; } ;
struct TYPE_2__ {struct snic_misc_stats misc; } ;
struct snic {unsigned int wq_count; unsigned int cq_count; int /*<<< orphan*/ * cq; TYPE_1__ s_stats; } ;

/* Variables and functions */
 unsigned int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  snic_io_cmpl_handler ; 
 unsigned int vnic_cq_fw_service (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
snic_fwcq_cmpl_handler(struct snic *snic, int io_cmpl_work)
{
	unsigned int num_ent = 0;	/* number cq entries processed */
	unsigned int cq_idx;
	unsigned int nent_per_cq;
	struct snic_misc_stats *misc_stats = &snic->s_stats.misc;

	for (cq_idx = snic->wq_count; cq_idx < snic->cq_count; cq_idx++) {
		nent_per_cq = vnic_cq_fw_service(&snic->cq[cq_idx],
						 snic_io_cmpl_handler,
						 io_cmpl_work);
		num_ent += nent_per_cq;

		if (nent_per_cq > atomic64_read(&misc_stats->max_cq_ents))
			atomic64_set(&misc_stats->max_cq_ents, nent_per_cq);
	}

	return num_ent;
}