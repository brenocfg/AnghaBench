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
typedef  int u32 ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA_TACTIVATE ; 
 int PA_TACTIVATE_TIME_UNIT_US ; 
 int /*<<< orphan*/  RX_MIN_ACTIVATETIME_CAPABILITY ; 
 int RX_MIN_ACTIVATETIME_UNIT_US ; 
 int /*<<< orphan*/  UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIC_ARG_MIB_SEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIC_ARG_MPHY_RX_GEN_SEL_INDEX (int /*<<< orphan*/ ) ; 
 int ufshcd_dme_peer_get (struct ufs_hba*,int /*<<< orphan*/ ,int*) ; 
 int ufshcd_dme_set (struct ufs_hba*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ufshcd_tune_pa_tactivate(struct ufs_hba *hba)
{
	int ret = 0;
	u32 peer_rx_min_activatetime = 0, tuned_pa_tactivate;

	ret = ufshcd_dme_peer_get(hba,
				  UIC_ARG_MIB_SEL(
					RX_MIN_ACTIVATETIME_CAPABILITY,
					UIC_ARG_MPHY_RX_GEN_SEL_INDEX(0)),
				  &peer_rx_min_activatetime);
	if (ret)
		goto out;

	/* make sure proper unit conversion is applied */
	tuned_pa_tactivate =
		((peer_rx_min_activatetime * RX_MIN_ACTIVATETIME_UNIT_US)
		 / PA_TACTIVATE_TIME_UNIT_US);
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(PA_TACTIVATE),
			     tuned_pa_tactivate);

out:
	return ret;
}