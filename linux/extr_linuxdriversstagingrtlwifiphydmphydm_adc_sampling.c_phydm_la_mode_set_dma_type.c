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
typedef  int /*<<< orphan*/  u8 ;
struct phy_dm_struct {int support_ic_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_UNCOND ; 
 int ODM_N_ANTDIV_SUPPORT ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int odm_adc_trigger_jaguar2 ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void phydm_la_mode_set_dma_type(void *dm_void, u8 la_dma_type)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	ODM_RT_TRACE(dm, ODM_COMP_UNCOND,
		     "2. [LA mode DMA setting] Dma_type = ((%d))\n",
		     la_dma_type);

	if (dm->support_ic_type & ODM_N_ANTDIV_SUPPORT)
		odm_set_bb_reg(dm, 0x9a0, 0xf00, la_dma_type); /*0x9A0[11:8]*/
	else
		odm_set_bb_reg(dm, odm_adc_trigger_jaguar2, 0xf00,
			       la_dma_type); /*0x95C[11:8]*/
}