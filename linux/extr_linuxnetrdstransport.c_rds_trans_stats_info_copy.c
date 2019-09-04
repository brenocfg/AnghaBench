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
struct rds_transport {unsigned int (* stats_info_copy ) (struct rds_info_iterator*,unsigned int) ;} ;
struct rds_info_iterator {int dummy; } ;

/* Variables and functions */
 int RDS_TRANS_COUNT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rds_info_iter_unmap (struct rds_info_iterator*) ; 
 int /*<<< orphan*/  rds_trans_sem ; 
 unsigned int stub1 (struct rds_info_iterator*,unsigned int) ; 
 struct rds_transport** transports ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

unsigned int rds_trans_stats_info_copy(struct rds_info_iterator *iter,
				       unsigned int avail)

{
	struct rds_transport *trans;
	unsigned int total = 0;
	unsigned int part;
	int i;

	rds_info_iter_unmap(iter);
	down_read(&rds_trans_sem);

	for (i = 0; i < RDS_TRANS_COUNT; i++) {
		trans = transports[i];
		if (!trans || !trans->stats_info_copy)
			continue;

		part = trans->stats_info_copy(iter, avail);
		avail -= min(avail, part);
		total += part;
	}

	up_read(&rds_trans_sem);

	return total;
}