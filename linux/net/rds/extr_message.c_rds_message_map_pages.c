#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scatterlist {int dummy; } ;
struct TYPE_6__ {unsigned int op_nents; int /*<<< orphan*/ * op_sg; } ;
struct TYPE_4__ {int /*<<< orphan*/  h_len; } ;
struct TYPE_5__ {TYPE_1__ i_hdr; } ;
struct rds_message {TYPE_3__ data; TYPE_2__ m_inc; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct rds_message* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RDS_MSG_PAGEVEC ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 struct rds_message* rds_message_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rds_message_alloc_sgs (struct rds_message*,int,int*) ; 
 int /*<<< orphan*/  rds_message_put (struct rds_message*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_set_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

struct rds_message *rds_message_map_pages(unsigned long *page_addrs, unsigned int total_len)
{
	struct rds_message *rm;
	unsigned int i;
	int num_sgs = DIV_ROUND_UP(total_len, PAGE_SIZE);
	int extra_bytes = num_sgs * sizeof(struct scatterlist);
	int ret;

	rm = rds_message_alloc(extra_bytes, GFP_NOWAIT);
	if (!rm)
		return ERR_PTR(-ENOMEM);

	set_bit(RDS_MSG_PAGEVEC, &rm->m_flags);
	rm->m_inc.i_hdr.h_len = cpu_to_be32(total_len);
	rm->data.op_nents = DIV_ROUND_UP(total_len, PAGE_SIZE);
	rm->data.op_sg = rds_message_alloc_sgs(rm, num_sgs, &ret);
	if (!rm->data.op_sg) {
		rds_message_put(rm);
		return ERR_PTR(ret);
	}

	for (i = 0; i < rm->data.op_nents; ++i) {
		sg_set_page(&rm->data.op_sg[i],
				virt_to_page(page_addrs[i]),
				PAGE_SIZE, 0);
	}

	return rm;
}