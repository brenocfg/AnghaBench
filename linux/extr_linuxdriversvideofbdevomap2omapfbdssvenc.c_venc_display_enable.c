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
struct omap_dss_device {int /*<<< orphan*/ * manager; } ;
struct TYPE_2__ {int /*<<< orphan*/  venc_lock; scalar_t__ wss_data; struct omap_dss_device output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ venc ; 
 int venc_power_on (struct omap_dss_device*) ; 

__attribute__((used)) static int venc_display_enable(struct omap_dss_device *dssdev)
{
	struct omap_dss_device *out = &venc.output;
	int r;

	DSSDBG("venc_display_enable\n");

	mutex_lock(&venc.venc_lock);

	if (out->manager == NULL) {
		DSSERR("Failed to enable display: no output/manager\n");
		r = -ENODEV;
		goto err0;
	}

	r = venc_power_on(dssdev);
	if (r)
		goto err0;

	venc.wss_data = 0;

	mutex_unlock(&venc.venc_lock);

	return 0;
err0:
	mutex_unlock(&venc.venc_lock);
	return r;
}