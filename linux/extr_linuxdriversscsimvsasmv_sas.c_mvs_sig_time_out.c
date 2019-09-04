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
typedef  size_t u8 ;
struct timer_list {int dummy; } ;
struct mvs_phy {struct mvs_info* mvi; } ;
struct mvs_info {size_t id; TYPE_1__* chip; struct mvs_phy* phy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* phy_reset ) (struct mvs_info*,size_t,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {size_t n_phy; } ;

/* Variables and functions */
 TYPE_2__* MVS_CHIP_DISP ; 
 int /*<<< orphan*/  MVS_HARD_RESET ; 
 struct mvs_phy* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_dprintk (char*,size_t) ; 
 struct mvs_phy* phy ; 
 int /*<<< orphan*/  stub1 (struct mvs_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void mvs_sig_time_out(struct timer_list *t)
{
	struct mvs_phy *phy = from_timer(phy, t, timer);
	struct mvs_info *mvi = phy->mvi;
	u8 phy_no;

	for (phy_no = 0; phy_no < mvi->chip->n_phy; phy_no++) {
		if (&mvi->phy[phy_no] == phy) {
			mv_dprintk("Get signature time out, reset phy %d\n",
				phy_no+mvi->id*mvi->chip->n_phy);
			MVS_CHIP_DISP->phy_reset(mvi, phy_no, MVS_HARD_RESET);
		}
	}
}