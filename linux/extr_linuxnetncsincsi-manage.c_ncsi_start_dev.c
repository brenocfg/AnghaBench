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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ncsi_dev_priv {int flags; TYPE_1__ ndev; int /*<<< orphan*/  work; } ;
struct ncsi_dev {scalar_t__ state; } ;

/* Variables and functions */
 int ENOTTY ; 
 int NCSI_DEV_HWA ; 
 int NCSI_DEV_PROBED ; 
 struct ncsi_dev_priv* TO_NCSI_DEV_PRIV (struct ncsi_dev*) ; 
 int ncsi_choose_active_channel (struct ncsi_dev_priv*) ; 
 scalar_t__ ncsi_dev_state_functional ; 
 scalar_t__ ncsi_dev_state_probe ; 
 scalar_t__ ncsi_dev_state_registered ; 
 int ncsi_enable_hwa (struct ncsi_dev_priv*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int ncsi_start_dev(struct ncsi_dev *nd)
{
	struct ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);
	int ret;

	if (nd->state != ncsi_dev_state_registered &&
	    nd->state != ncsi_dev_state_functional)
		return -ENOTTY;

	if (!(ndp->flags & NCSI_DEV_PROBED)) {
		nd->state = ncsi_dev_state_probe;
		schedule_work(&ndp->work);
		return 0;
	}

	if (ndp->flags & NCSI_DEV_HWA) {
		netdev_info(ndp->ndev.dev, "NCSI: Enabling HWA mode\n");
		ret = ncsi_enable_hwa(ndp);
	} else {
		ret = ncsi_choose_active_channel(ndp);
	}

	return ret;
}