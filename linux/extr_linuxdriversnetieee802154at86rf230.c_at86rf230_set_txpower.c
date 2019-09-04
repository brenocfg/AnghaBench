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
struct ieee802154_hw {struct at86rf230_local* priv; } ;
struct at86rf230_local {TYPE_1__* data; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int (* set_txpower ) (struct at86rf230_local*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct at86rf230_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
at86rf230_set_txpower(struct ieee802154_hw *hw, s32 mbm)
{
	struct at86rf230_local *lp = hw->priv;

	return lp->data->set_txpower(lp, mbm);
}