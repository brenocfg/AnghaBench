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
struct cw1200_common {TYPE_1__* hw; int /*<<< orphan*/  bh_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*) ; 

int cw1200_can_suspend(struct cw1200_common *priv)
{
	if (atomic_read(&priv->bh_rx)) {
		wiphy_dbg(priv->hw->wiphy, "Suspend interrupted.\n");
		return 0;
	}
	return 1;
}