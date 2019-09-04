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
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;
struct ath10k {void* cal_file; int /*<<< orphan*/  dev; TYPE_1__ hif; void* pre_cal_file; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ATH10K_FW_DIR ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  ath10k_bus_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 void* ath10k_fetch_fw_file (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_fetch_cal_file(struct ath10k *ar)
{
	char filename[100];

	/* pre-cal-<bus>-<id>.bin */
	scnprintf(filename, sizeof(filename), "pre-cal-%s-%s.bin",
		  ath10k_bus_str(ar->hif.bus), dev_name(ar->dev));

	ar->pre_cal_file = ath10k_fetch_fw_file(ar, ATH10K_FW_DIR, filename);
	if (!IS_ERR(ar->pre_cal_file))
		goto success;

	/* cal-<bus>-<id>.bin */
	scnprintf(filename, sizeof(filename), "cal-%s-%s.bin",
		  ath10k_bus_str(ar->hif.bus), dev_name(ar->dev));

	ar->cal_file = ath10k_fetch_fw_file(ar, ATH10K_FW_DIR, filename);
	if (IS_ERR(ar->cal_file))
		/* calibration file is optional, don't print any warnings */
		return PTR_ERR(ar->cal_file);
success:
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "found calibration file %s/%s\n",
		   ATH10K_FW_DIR, filename);

	return 0;
}