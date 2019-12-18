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
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 

struct scatterlist *rds_message_alloc_sgs(struct rds_message *rm, int nents,
					  int *ret)
{
	struct scatterlist *sg_first = (struct scatterlist *) &rm[1];
	struct scatterlist *sg_ret;

	if (WARN_ON(!ret))
		return NULL;

	if (nents <= 0) {
		pr_warn("rds: alloc sgs failed! nents <= 0\n");
		*ret = -EINVAL;
		return NULL;
	}

	if (rm->m_used_sgs + nents > rm->m_total_sgs) {
		pr_warn("rds: alloc sgs failed! total %d used %d nents %d\n",
			rm->m_total_sgs, rm->m_used_sgs, nents);
		*ret = -ENOMEM;
		return NULL;
	}

	sg_ret = &sg_first[rm->m_used_sgs];
	sg_init_table(sg_ret, nents);
	rm->m_used_sgs += nents;

	return sg_ret;
}