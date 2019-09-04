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
struct bd_list {int eqp_bdi; int hwd_bdi; int max_bdi; int num_tabs; int num_bds_table; } ;
struct bdc_ep {struct bdc* bdc; struct bd_list bd_list; } ;
struct bdc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ bdi_to_tbi (struct bdc_ep*,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int bd_available_ep(struct bdc_ep *ep)
{
	struct bd_list *bd_list = &ep->bd_list;
	int available1, available2;
	struct bdc *bdc = ep->bdc;
	int chain_bd1, chain_bd2;
	int available_bd = 0;

	available1 = available2 = chain_bd1 = chain_bd2 = 0;
	/* if empty then we have all bd's available - number of chain bd's */
	if (bd_list->eqp_bdi == bd_list->hwd_bdi)
		return bd_list->max_bdi - bd_list->num_tabs;

	/*
	 * Depending upon where eqp and dqp pointers are, caculate number
	 * of avaialble bd's
	 */
	if (bd_list->hwd_bdi < bd_list->eqp_bdi) {
		/* available bd's are from eqp..max_bds + 0..dqp - chain_bds */
		available1 = bd_list->max_bdi - bd_list->eqp_bdi;
		available2 = bd_list->hwd_bdi;
		chain_bd1 = available1 / bd_list->num_bds_table;
		chain_bd2 = available2 / bd_list->num_bds_table;
		dev_vdbg(bdc->dev, "chain_bd1:%d chain_bd2:%d\n",
						chain_bd1, chain_bd2);
		available_bd = available1 + available2 - chain_bd1 - chain_bd2;
	} else {
		/* available bd's are from eqp..dqp - number of chain bd's */
		available1 = bd_list->hwd_bdi -  bd_list->eqp_bdi;
		/* if gap between eqp and dqp is less than NUM_BDS_PER_TABLE */
		if ((bd_list->hwd_bdi - bd_list->eqp_bdi)
					<= bd_list->num_bds_table) {
			/* If there any chain bd in between */
			if (!(bdi_to_tbi(ep, bd_list->hwd_bdi)
					== bdi_to_tbi(ep, bd_list->eqp_bdi))) {
				available_bd = available1 - 1;
			}
		} else {
			chain_bd1 = available1 / bd_list->num_bds_table;
			available_bd = available1 - chain_bd1;
		}
	}
	/*
	 * we need to keep one extra bd to check if ring is full or empty so
	 * reduce by 1
	 */
	available_bd--;
	dev_vdbg(bdc->dev, "available_bd:%d\n", available_bd);

	return available_bd;
}