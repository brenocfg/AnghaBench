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
struct rpmh_ctrlr {int dirty; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  ctrlr_to_drv (struct rpmh_ctrlr*) ; 
 struct rpmh_ctrlr* get_rpmh_ctrlr (struct device const*) ; 
 int /*<<< orphan*/  invalidate_batch (struct rpmh_ctrlr*) ; 
 int rpmh_rsc_invalidate (int /*<<< orphan*/ ) ; 

int rpmh_invalidate(const struct device *dev)
{
	struct rpmh_ctrlr *ctrlr = get_rpmh_ctrlr(dev);
	int ret;

	invalidate_batch(ctrlr);
	ctrlr->dirty = true;

	do {
		ret = rpmh_rsc_invalidate(ctrlr_to_drv(ctrlr));
	} while (ret == -EAGAIN);

	return ret;
}