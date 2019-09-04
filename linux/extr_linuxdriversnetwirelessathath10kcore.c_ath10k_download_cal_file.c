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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct firmware const*) ; 
 int PTR_ERR (struct firmware const*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int ath10k_download_board_data (struct ath10k*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 

__attribute__((used)) static int ath10k_download_cal_file(struct ath10k *ar,
				    const struct firmware *file)
{
	int ret;

	if (!file)
		return -ENOENT;

	if (IS_ERR(file))
		return PTR_ERR(file);

	ret = ath10k_download_board_data(ar, file->data, file->size);
	if (ret) {
		ath10k_err(ar, "failed to download cal_file data: %d\n", ret);
		return ret;
	}

	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot cal file downloaded\n");

	return 0;
}