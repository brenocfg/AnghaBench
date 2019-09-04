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
typedef  void* u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct il_chain_noise_data {scalar_t__* delta_gain_code; int radio_write; int /*<<< orphan*/  state; int /*<<< orphan*/ * disconn_array; } ;
struct il_priv {struct il_chain_noise_data chain_noise_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  op_code; } ;
struct il_calib_diff_gain_cmd {int diff_gain_a; int diff_gain_b; int diff_gain_c; TYPE_1__ hdr; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 scalar_t__ CHAIN_NOISE_DELTA_GAIN_INIT_VAL ; 
 scalar_t__ CHAIN_NOISE_MAX_DELTA_GAIN_CODE ; 
 int /*<<< orphan*/  C_PHY_CALIBRATION ; 
 int /*<<< orphan*/  D_CALIB (char*,...) ; 
 int /*<<< orphan*/  IL_CHAIN_NOISE_CALIBRATED ; 
 int /*<<< orphan*/  IL_PHY_CALIBRATE_DIFF_GAIN_CMD ; 
 int NUM_RX_CHAINS ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il_calib_diff_gain_cmd*) ; 
 int /*<<< orphan*/  memset (struct il_calib_diff_gain_cmd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,void*) ; 

__attribute__((used)) static void
il4965_gain_computation(struct il_priv *il, u32 * average_noise,
			u16 min_average_noise_antenna_i, u32 min_average_noise,
			u8 default_chain)
{
	int i, ret;
	struct il_chain_noise_data *data = &il->chain_noise_data;

	data->delta_gain_code[min_average_noise_antenna_i] = 0;

	for (i = default_chain; i < NUM_RX_CHAINS; i++) {
		s32 delta_g = 0;

		if (!data->disconn_array[i] &&
		    data->delta_gain_code[i] ==
		    CHAIN_NOISE_DELTA_GAIN_INIT_VAL) {
			delta_g = average_noise[i] - min_average_noise;
			data->delta_gain_code[i] = (u8) ((delta_g * 10) / 15);
			data->delta_gain_code[i] =
			    min(data->delta_gain_code[i],
				(u8) CHAIN_NOISE_MAX_DELTA_GAIN_CODE);

			data->delta_gain_code[i] =
			    (data->delta_gain_code[i] | (1 << 2));
		} else {
			data->delta_gain_code[i] = 0;
		}
	}
	D_CALIB("delta_gain_codes: a %d b %d c %d\n", data->delta_gain_code[0],
		data->delta_gain_code[1], data->delta_gain_code[2]);

	/* Differential gain gets sent to uCode only once */
	if (!data->radio_write) {
		struct il_calib_diff_gain_cmd cmd;
		data->radio_write = 1;

		memset(&cmd, 0, sizeof(cmd));
		cmd.hdr.op_code = IL_PHY_CALIBRATE_DIFF_GAIN_CMD;
		cmd.diff_gain_a = data->delta_gain_code[0];
		cmd.diff_gain_b = data->delta_gain_code[1];
		cmd.diff_gain_c = data->delta_gain_code[2];
		ret = il_send_cmd_pdu(il, C_PHY_CALIBRATION, sizeof(cmd), &cmd);
		if (ret)
			D_CALIB("fail sending cmd " "C_PHY_CALIBRATION\n");

		/* TODO we might want recalculate
		 * rx_chain in rxon cmd */

		/* Mark so we run this algo only once! */
		data->state = IL_CHAIN_NOISE_CALIBRATED;
	}
}