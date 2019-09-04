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
struct omap_dss_device {TYPE_1__* dst; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/ * src; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,...) ; 
 int EINVAL ; 
 scalar_t__ OMAP_DSS_DISPLAY_DISABLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  output_lock ; 

int omapdss_output_unset_device(struct omap_dss_device *out)
{
	int r;

	mutex_lock(&output_lock);

	if (!out->dst) {
		DSSERR("output doesn't have a device connected to it\n");
		r = -EINVAL;
		goto err;
	}

	if (out->dst->state != OMAP_DSS_DISPLAY_DISABLED) {
		DSSERR("device %s is not disabled, cannot unset device\n",
				out->dst->name);
		r = -EINVAL;
		goto err;
	}

	out->dst->src = NULL;
	out->dst = NULL;

	mutex_unlock(&output_lock);

	return 0;
err:
	mutex_unlock(&output_lock);

	return r;
}