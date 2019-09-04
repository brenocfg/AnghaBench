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
typedef  int /*<<< orphan*/  u32 ;
struct owl_sps_domain {TYPE_2__* sps; TYPE_1__* info; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int /*<<< orphan*/  pwr_bit; int /*<<< orphan*/  ack_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int owl_sps_set_pg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int owl_sps_set_power(struct owl_sps_domain *pd, bool enable)
{
	u32 pwr_mask, ack_mask;

	ack_mask = BIT(pd->info->ack_bit);
	pwr_mask = BIT(pd->info->pwr_bit);

	return owl_sps_set_pg(pd->sps->base, pwr_mask, ack_mask, enable);
}