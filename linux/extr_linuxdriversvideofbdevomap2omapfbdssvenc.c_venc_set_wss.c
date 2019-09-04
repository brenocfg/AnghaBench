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
typedef  int u32 ;
struct venc_config {int bstamp_wss_data; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_2__ {int wss_data; int /*<<< orphan*/  venc_lock; int /*<<< orphan*/  timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSDBG (char*) ; 
 int /*<<< orphan*/  VENC_BSTAMP_WSS_DATA ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ venc ; 
 int venc_runtime_get () ; 
 int /*<<< orphan*/  venc_runtime_put () ; 
 struct venc_config* venc_timings_to_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venc_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venc_set_wss(struct omap_dss_device *dssdev, u32 wss)
{
	const struct venc_config *config;
	int r;

	DSSDBG("venc_set_wss\n");

	mutex_lock(&venc.venc_lock);

	config = venc_timings_to_config(&venc.timings);

	/* Invert due to VENC_L21_WC_CTL:INV=1 */
	venc.wss_data = (wss ^ 0xfffff) << 8;

	r = venc_runtime_get();
	if (r)
		goto err;

	venc_write_reg(VENC_BSTAMP_WSS_DATA, config->bstamp_wss_data |
			venc.wss_data);

	venc_runtime_put();

err:
	mutex_unlock(&venc.venc_lock);

	return r;
}