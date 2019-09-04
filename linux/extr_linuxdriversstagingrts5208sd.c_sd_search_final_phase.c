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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct timing_phase_path {int start; int end; int len; int mid; } ;
struct sd_info {int dummy; } ;
struct rtsx_chip {scalar_t__ sd_default_tx_phase; scalar_t__ sd_default_rx_phase; struct sd_info sd_card; } ;

/* Variables and functions */
 scalar_t__ CHK_SD_SDR104 (struct sd_info*) ; 
 scalar_t__ CHK_SD_SDR50 (struct sd_info*) ; 
 int MAX_PHASE ; 
 scalar_t__ TUNE_RX ; 
 scalar_t__ TUNE_TX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 

__attribute__((used)) static u8 sd_search_final_phase(struct rtsx_chip *chip, u32 phase_map,
				u8 tune_dir)
{
	struct sd_info *sd_card = &chip->sd_card;
	struct timing_phase_path path[MAX_PHASE + 1];
	int i, j, cont_path_cnt;
	bool new_block;
	int max_len, final_path_idx;
	u8 final_phase = 0xFF;

	if (phase_map == 0xFFFFFFFF) {
		if (tune_dir == TUNE_RX)
			final_phase = (u8)chip->sd_default_rx_phase;
		else
			final_phase = (u8)chip->sd_default_tx_phase;

		goto search_finish;
	}

	cont_path_cnt = 0;
	new_block = true;
	j = 0;
	for (i = 0; i < MAX_PHASE + 1; i++) {
		if (phase_map & (1 << i)) {
			if (new_block) {
				new_block = false;
				j = cont_path_cnt++;
				path[j].start = i;
				path[j].end = i;
			} else {
				path[j].end = i;
			}
		} else {
			new_block = true;
			if (cont_path_cnt) {
				int idx = cont_path_cnt - 1;

				path[idx].len = path[idx].end -
					path[idx].start + 1;
				path[idx].mid = path[idx].start +
					path[idx].len / 2;
			}
		}
	}

	if (cont_path_cnt == 0) {
		dev_dbg(rtsx_dev(chip), "No continuous phase path\n");
		goto search_finish;
	} else {
		int idx = cont_path_cnt - 1;

		path[idx].len = path[idx].end - path[idx].start + 1;
		path[idx].mid = path[idx].start + path[idx].len / 2;
	}

	if ((path[0].start == 0) &&
	    (path[cont_path_cnt - 1].end == MAX_PHASE)) {
		path[0].start = path[cont_path_cnt - 1].start - MAX_PHASE - 1;
		path[0].len += path[cont_path_cnt - 1].len;
		path[0].mid = path[0].start + path[0].len / 2;
		if (path[0].mid < 0)
			path[0].mid += MAX_PHASE + 1;

		cont_path_cnt--;
	}

	max_len = 0;
	final_phase = 0;
	final_path_idx = 0;
	for (i = 0; i < cont_path_cnt; i++) {
		if (path[i].len > max_len) {
			max_len = path[i].len;
			final_phase = (u8)path[i].mid;
			final_path_idx = i;
		}

		dev_dbg(rtsx_dev(chip), "path[%d].start = %d\n",
			i, path[i].start);
		dev_dbg(rtsx_dev(chip), "path[%d].end = %d\n", i, path[i].end);
		dev_dbg(rtsx_dev(chip), "path[%d].len = %d\n", i, path[i].len);
		dev_dbg(rtsx_dev(chip), "path[%d].mid = %d\n", i, path[i].mid);
		dev_dbg(rtsx_dev(chip), "\n");
	}

	if (tune_dir == TUNE_TX) {
		if (CHK_SD_SDR104(sd_card)) {
			if (max_len > 15) {
				int temp_mid = (max_len - 16) / 2;
				int temp_final_phase =
					path[final_path_idx].end -
					(max_len - (6 + temp_mid));

				if (temp_final_phase < 0)
					final_phase = (u8)(temp_final_phase +
							MAX_PHASE + 1);
				else
					final_phase = (u8)temp_final_phase;
			}
		} else if (CHK_SD_SDR50(sd_card)) {
			if (max_len > 12) {
				int temp_mid = (max_len - 13) / 2;
				int temp_final_phase =
					path[final_path_idx].end -
					(max_len - (3 + temp_mid));

				if (temp_final_phase < 0)
					final_phase = (u8)(temp_final_phase +
							MAX_PHASE + 1);
				else
					final_phase = (u8)temp_final_phase;
			}
		}
	}

search_finish:
	dev_dbg(rtsx_dev(chip), "Final chosen phase: %d\n", final_phase);
	return final_phase;
}