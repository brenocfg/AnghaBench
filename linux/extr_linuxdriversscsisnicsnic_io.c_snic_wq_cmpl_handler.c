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
struct TYPE_3__ {int /*<<< orphan*/  last_ack_time; } ;
struct TYPE_4__ {TYPE_1__ misc; } ;
struct snic {unsigned int wq_count; int /*<<< orphan*/ * cq; TYPE_2__ s_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  snic_wq_cmpl_handler_cont ; 
 scalar_t__ svnic_cq_service (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
snic_wq_cmpl_handler(struct snic *snic, int work_to_do)
{
	unsigned int work_done = 0;
	unsigned int i;

	snic->s_stats.misc.last_ack_time = jiffies;
	for (i = 0; i < snic->wq_count; i++) {
		work_done += svnic_cq_service(&snic->cq[i],
					      work_to_do,
					      snic_wq_cmpl_handler_cont,
					      NULL);
	}

	return work_done;
}