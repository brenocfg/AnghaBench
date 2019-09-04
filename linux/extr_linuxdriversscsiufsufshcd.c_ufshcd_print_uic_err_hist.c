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
struct ufs_uic_err_reg_hist {int pos; scalar_t__* reg; int /*<<< orphan*/ * tstamp; } ;
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int UIC_ERR_REG_HIST_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_print_uic_err_hist(struct ufs_hba *hba,
		struct ufs_uic_err_reg_hist *err_hist, char *err_name)
{
	int i;

	for (i = 0; i < UIC_ERR_REG_HIST_LENGTH; i++) {
		int p = (i + err_hist->pos - 1) % UIC_ERR_REG_HIST_LENGTH;

		if (err_hist->reg[p] == 0)
			continue;
		dev_err(hba->dev, "%s[%d] = 0x%x at %lld us\n", err_name, i,
			err_hist->reg[p], ktime_to_us(err_hist->tstamp[p]));
	}
}