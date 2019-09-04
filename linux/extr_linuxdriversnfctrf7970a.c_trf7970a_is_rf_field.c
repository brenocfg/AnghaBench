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
typedef  int u8 ;
struct trf7970a {int chip_status_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRF7970A_CHIP_STATUS_CTRL ; 
 int TRF7970A_CHIP_STATUS_REC_ON ; 
 int /*<<< orphan*/  TRF7970A_CMD_TEST_EXT_RF ; 
 int /*<<< orphan*/  TRF7970A_RSSI_OSC_STATUS ; 
 int TRF7970A_RSSI_OSC_STATUS_RSSI_MASK ; 
 int trf7970a_cmd (struct trf7970a*,int /*<<< orphan*/ ) ; 
 int trf7970a_read (struct trf7970a*,int /*<<< orphan*/ ,int*) ; 
 int trf7970a_write (struct trf7970a*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int trf7970a_is_rf_field(struct trf7970a *trf, bool *is_rf_field)
{
	int ret;
	u8 rssi;

	ret = trf7970a_write(trf, TRF7970A_CHIP_STATUS_CTRL,
			     trf->chip_status_ctrl |
			     TRF7970A_CHIP_STATUS_REC_ON);
	if (ret)
		return ret;

	ret = trf7970a_cmd(trf, TRF7970A_CMD_TEST_EXT_RF);
	if (ret)
		return ret;

	usleep_range(50, 60);

	ret = trf7970a_read(trf, TRF7970A_RSSI_OSC_STATUS, &rssi);
	if (ret)
		return ret;

	ret = trf7970a_write(trf, TRF7970A_CHIP_STATUS_CTRL,
			     trf->chip_status_ctrl);
	if (ret)
		return ret;

	if (rssi & TRF7970A_RSSI_OSC_STATUS_RSSI_MASK)
		*is_rf_field = true;
	else
		*is_rf_field = false;

	return 0;
}