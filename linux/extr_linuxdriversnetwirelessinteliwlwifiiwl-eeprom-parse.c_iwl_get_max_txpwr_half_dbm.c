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
struct iwl_nvm_data {int valid_tx_ant; } ;
struct iwl_eeprom_enhanced_txpwr {scalar_t__ chain_a_max; scalar_t__ chain_b_max; scalar_t__ chain_c_max; scalar_t__ mimo2_max; scalar_t__ mimo3_max; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int ANT_A ; 
 int ANT_AB ; 
 int ANT_ABC ; 
 int ANT_AC ; 
 int ANT_B ; 
 int ANT_BC ; 
 int ANT_C ; 

__attribute__((used)) static s8 iwl_get_max_txpwr_half_dbm(const struct iwl_nvm_data *data,
				     struct iwl_eeprom_enhanced_txpwr *txp)
{
	s8 result = 0; /* (.5 dBm) */

	/* Take the highest tx power from any valid chains */
	if (data->valid_tx_ant & ANT_A && txp->chain_a_max > result)
		result = txp->chain_a_max;

	if (data->valid_tx_ant & ANT_B && txp->chain_b_max > result)
		result = txp->chain_b_max;

	if (data->valid_tx_ant & ANT_C && txp->chain_c_max > result)
		result = txp->chain_c_max;

	if ((data->valid_tx_ant == ANT_AB ||
	     data->valid_tx_ant == ANT_BC ||
	     data->valid_tx_ant == ANT_AC) && txp->mimo2_max > result)
		result = txp->mimo2_max;

	if (data->valid_tx_ant == ANT_ABC && txp->mimo3_max > result)
		result = txp->mimo3_max;

	return result;
}