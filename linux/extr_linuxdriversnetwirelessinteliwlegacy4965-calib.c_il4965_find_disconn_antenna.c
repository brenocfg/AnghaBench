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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_6__ {int valid_rx_ant; scalar_t__ valid_tx_ant; scalar_t__ tx_chains_num; } ;
struct TYPE_5__ {int active_chains; } ;
struct il_priv {TYPE_3__ hw_params; TYPE_2__ chain_noise_data; TYPE_1__* cfg; } ;
struct il_chain_noise_data {int chain_signal_a; int chain_signal_b; int chain_signal_c; int* disconn_array; int active_chains; } ;
typedef  int s32 ;
struct TYPE_4__ {int chain_noise_num_beacons; int /*<<< orphan*/  valid_tx_ant; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  D_CALIB (char*,int,...) ; 
 int MAXIMUM_ALLOWED_PATHLOSS ; 
 int NUM_RX_CHAINS ; 
 scalar_t__ il4965_find_first_chain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
il4965_find_disconn_antenna(struct il_priv *il, u32 * average_sig,
			    struct il_chain_noise_data *data)
{
	u32 active_chains = 0;
	u32 max_average_sig;
	u16 max_average_sig_antenna_i;
	u8 num_tx_chains;
	u8 first_chain;
	u16 i = 0;

	average_sig[0] =
	    data->chain_signal_a /
	    il->cfg->chain_noise_num_beacons;
	average_sig[1] =
	    data->chain_signal_b /
	    il->cfg->chain_noise_num_beacons;
	average_sig[2] =
	    data->chain_signal_c /
	    il->cfg->chain_noise_num_beacons;

	if (average_sig[0] >= average_sig[1]) {
		max_average_sig = average_sig[0];
		max_average_sig_antenna_i = 0;
		active_chains = (1 << max_average_sig_antenna_i);
	} else {
		max_average_sig = average_sig[1];
		max_average_sig_antenna_i = 1;
		active_chains = (1 << max_average_sig_antenna_i);
	}

	if (average_sig[2] >= max_average_sig) {
		max_average_sig = average_sig[2];
		max_average_sig_antenna_i = 2;
		active_chains = (1 << max_average_sig_antenna_i);
	}

	D_CALIB("average_sig: a %d b %d c %d\n", average_sig[0], average_sig[1],
		average_sig[2]);
	D_CALIB("max_average_sig = %d, antenna %d\n", max_average_sig,
		max_average_sig_antenna_i);

	/* Compare signal strengths for all 3 receivers. */
	for (i = 0; i < NUM_RX_CHAINS; i++) {
		if (i != max_average_sig_antenna_i) {
			s32 rssi_delta = (max_average_sig - average_sig[i]);

			/* If signal is very weak, compared with
			 * strongest, mark it as disconnected. */
			if (rssi_delta > MAXIMUM_ALLOWED_PATHLOSS)
				data->disconn_array[i] = 1;
			else
				active_chains |= (1 << i);
			D_CALIB("i = %d  rssiDelta = %d  "
				"disconn_array[i] = %d\n", i, rssi_delta,
				data->disconn_array[i]);
		}
	}

	/*
	 * The above algorithm sometimes fails when the ucode
	 * reports 0 for all chains. It's not clear why that
	 * happens to start with, but it is then causing trouble
	 * because this can make us enable more chains than the
	 * hardware really has.
	 *
	 * To be safe, simply mask out any chains that we know
	 * are not on the device.
	 */
	active_chains &= il->hw_params.valid_rx_ant;

	num_tx_chains = 0;
	for (i = 0; i < NUM_RX_CHAINS; i++) {
		/* loops on all the bits of
		 * il->hw_setting.valid_tx_ant */
		u8 ant_msk = (1 << i);
		if (!(il->hw_params.valid_tx_ant & ant_msk))
			continue;

		num_tx_chains++;
		if (data->disconn_array[i] == 0)
			/* there is a Tx antenna connected */
			break;
		if (num_tx_chains == il->hw_params.tx_chains_num &&
		    data->disconn_array[i]) {
			/*
			 * If all chains are disconnected
			 * connect the first valid tx chain
			 */
			first_chain =
			    il4965_find_first_chain(il->cfg->valid_tx_ant);
			data->disconn_array[first_chain] = 0;
			active_chains |= BIT(first_chain);
			D_CALIB("All Tx chains are disconnected"
				"- declare %d as connected\n", first_chain);
			break;
		}
	}

	if (active_chains != il->hw_params.valid_rx_ant &&
	    active_chains != il->chain_noise_data.active_chains)
		D_CALIB("Detected that not all antennas are connected! "
			"Connected: %#x, valid: %#x.\n", active_chains,
			il->hw_params.valid_rx_ant);

	/* Save for use within RXON, TX, SCAN commands, etc. */
	data->active_chains = active_chains;
	D_CALIB("active_chains (bitwise) = 0x%x\n", active_chains);
}