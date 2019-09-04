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
struct scatterlist {int dummy; } ;
struct rds_message {int m_used_sgs; int m_total_sgs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 

struct scatterlist *rds_message_alloc_sgs(struct rds_message *rm, int nents)
{
	struct scatterlist *sg_first = (struct scatterlist *) &rm[1];
	struct scatterlist *sg_ret;

	WARN_ON(rm->m_used_sgs + nents > rm->m_total_sgs);
	WARN_ON(!nents);

	if (rm->m_used_sgs + nents > rm->m_total_sgs)
		return NULL;

	sg_ret = &sg_first[rm->m_used_sgs];
	sg_init_table(sg_ret, nents);
	rm->m_used_sgs += nents;

	return sg_ret;
}