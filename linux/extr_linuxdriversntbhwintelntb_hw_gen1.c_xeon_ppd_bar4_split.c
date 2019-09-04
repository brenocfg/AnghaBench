#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct intel_ntb_dev {TYPE_2__ ntb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int XEON_PPD_SPLIT_BAR_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline int xeon_ppd_bar4_split(struct intel_ntb_dev *ndev, u8 ppd)
{
	if (ppd & XEON_PPD_SPLIT_BAR_MASK) {
		dev_dbg(&ndev->ntb.pdev->dev, "PPD %d split bar\n", ppd);
		return 1;
	}
	return 0;
}