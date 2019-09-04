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
typedef  scalar_t__ u32 ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PA_LOCAL_TX_LCC_ENABLE ; 
 scalar_t__ UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_dme_get (struct ufs_hba*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  ufshcd_dme_set (struct ufs_hba*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufs_intel_disable_lcc(struct ufs_hba *hba)
{
	u32 attr = UIC_ARG_MIB(PA_LOCAL_TX_LCC_ENABLE);
	u32 lcc_enable = 0;

	ufshcd_dme_get(hba, attr, &lcc_enable);
	if (lcc_enable)
		ufshcd_dme_set(hba, attr, 0);

	return 0;
}