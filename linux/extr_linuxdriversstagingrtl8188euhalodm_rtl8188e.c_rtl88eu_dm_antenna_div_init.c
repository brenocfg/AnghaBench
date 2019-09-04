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
struct odm_dm_struct {scalar_t__ AntDivType; } ;

/* Variables and functions */
 scalar_t__ CGCS_RX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 int /*<<< orphan*/  dm_fast_training_init (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  dm_rx_hw_antena_div_init (struct odm_dm_struct*) ; 
 int /*<<< orphan*/  dm_trx_hw_antenna_div_init (struct odm_dm_struct*) ; 

void rtl88eu_dm_antenna_div_init(struct odm_dm_struct *dm_odm)
{
	if (dm_odm->AntDivType == CGCS_RX_HW_ANTDIV)
		dm_rx_hw_antena_div_init(dm_odm);
	else if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
		dm_trx_hw_antenna_div_init(dm_odm);
	else if (dm_odm->AntDivType == CG_TRX_SMART_ANTDIV)
		dm_fast_training_init(dm_odm);
}