#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_ioc_s {TYPE_1__* ioc_hwif; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ioc_isr_mode_set; int /*<<< orphan*/  ioc_lpu_read_stat; int /*<<< orphan*/  ioc_map_port; int /*<<< orphan*/  ioc_reg_init; int /*<<< orphan*/  ioc_pll_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_ct2_lpu_read_stat ; 
 int /*<<< orphan*/  bfa_ioc_ct2_map_port ; 
 int /*<<< orphan*/  bfa_ioc_ct2_pll_init ; 
 int /*<<< orphan*/  bfa_ioc_ct2_reg_init ; 
 int /*<<< orphan*/  bfa_ioc_set_ctx_hwif (struct bfa_ioc_s*,TYPE_1__*) ; 
 TYPE_1__ hwif_ct2 ; 

void
bfa_ioc_set_ct2_hwif(struct bfa_ioc_s *ioc)
{
	bfa_ioc_set_ctx_hwif(ioc, &hwif_ct2);

	hwif_ct2.ioc_pll_init = bfa_ioc_ct2_pll_init;
	hwif_ct2.ioc_reg_init = bfa_ioc_ct2_reg_init;
	hwif_ct2.ioc_map_port = bfa_ioc_ct2_map_port;
	hwif_ct2.ioc_lpu_read_stat = bfa_ioc_ct2_lpu_read_stat;
	hwif_ct2.ioc_isr_mode_set = NULL;
	ioc->ioc_hwif = &hwif_ct2;
}