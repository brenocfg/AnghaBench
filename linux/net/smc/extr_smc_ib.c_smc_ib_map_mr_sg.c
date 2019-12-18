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
struct smc_buf_desc {TYPE_1__* sgt; int /*<<< orphan*/ * mr_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t SMC_SINGLE_LINK ; 
 int ib_map_mr_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_ib_map_mr_sg(struct smc_buf_desc *buf_slot)
{
	unsigned int offset = 0;
	int sg_num;

	/* map the largest prefix of a dma mapped SG list */
	sg_num = ib_map_mr_sg(buf_slot->mr_rx[SMC_SINGLE_LINK],
			      buf_slot->sgt[SMC_SINGLE_LINK].sgl,
			      buf_slot->sgt[SMC_SINGLE_LINK].orig_nents,
			      &offset, PAGE_SIZE);

	return sg_num;
}