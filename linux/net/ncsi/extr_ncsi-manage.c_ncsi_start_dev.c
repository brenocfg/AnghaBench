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
struct ncsi_dev_priv {int flags; int /*<<< orphan*/  work; scalar_t__ package_probe_id; } ;
struct ncsi_dev {scalar_t__ state; } ;

/* Variables and functions */
 int ENOTTY ; 
 int NCSI_DEV_PROBED ; 
 struct ncsi_dev_priv* TO_NCSI_DEV_PRIV (struct ncsi_dev*) ; 
 scalar_t__ ncsi_dev_state_functional ; 
 scalar_t__ ncsi_dev_state_probe ; 
 scalar_t__ ncsi_dev_state_registered ; 
 int ncsi_reset_dev (struct ncsi_dev*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int ncsi_start_dev(struct ncsi_dev *nd)
{
	struct ncsi_dev_priv *ndp = TO_NCSI_DEV_PRIV(nd);

	if (nd->state != ncsi_dev_state_registered &&
	    nd->state != ncsi_dev_state_functional)
		return -ENOTTY;

	if (!(ndp->flags & NCSI_DEV_PROBED)) {
		ndp->package_probe_id = 0;
		nd->state = ncsi_dev_state_probe;
		schedule_work(&ndp->work);
		return 0;
	}

	return ncsi_reset_dev(nd);
}