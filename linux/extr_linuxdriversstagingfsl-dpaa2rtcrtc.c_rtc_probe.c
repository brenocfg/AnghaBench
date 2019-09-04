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
typedef  int /*<<< orphan*/  u32 ;
struct ptp_dpaa2_priv {int /*<<< orphan*/  clock; int /*<<< orphan*/  caps; int /*<<< orphan*/  freq_comp; struct fsl_mc_device* rtc_mc_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  mc_handle; TYPE_1__ obj_desc; struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct ptp_dpaa2_priv*) ; 
 int /*<<< orphan*/  dpaa2_phc_index ; 
 int /*<<< orphan*/  dprtc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dprtc_get_freq_compensation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dprtc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fsl_mc_portal_allocate (struct fsl_mc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ptp_dpaa2_priv*) ; 
 struct ptp_dpaa2_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_register (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  ptp_dpaa2_caps ; 

__attribute__((used)) static int rtc_probe(struct fsl_mc_device *mc_dev)
{
	struct device *dev = &mc_dev->dev;
	struct ptp_dpaa2_priv *ptp_dpaa2;
	u32 tmr_add = 0;
	int err;

	ptp_dpaa2 = kzalloc(sizeof(*ptp_dpaa2), GFP_KERNEL);
	if (!ptp_dpaa2)
		return -ENOMEM;

	err = fsl_mc_portal_allocate(mc_dev, 0, &mc_dev->mc_io);
	if (err) {
		if (err == -ENXIO)
			err = -EPROBE_DEFER;
		else
			dev_err(dev, "fsl_mc_portal_allocate err %d\n", err);
		goto err_exit;
	}

	err = dprtc_open(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			 &mc_dev->mc_handle);
	if (err) {
		dev_err(dev, "dprtc_open err %d\n", err);
		goto err_free_mcp;
	}

	ptp_dpaa2->rtc_mc_dev = mc_dev;

	err = dprtc_get_freq_compensation(mc_dev->mc_io, 0,
					  mc_dev->mc_handle, &tmr_add);
	if (err) {
		dev_err(dev, "dprtc_get_freq_compensation err %d\n", err);
		goto err_close;
	}

	ptp_dpaa2->freq_comp = tmr_add;
	ptp_dpaa2->caps = ptp_dpaa2_caps;

	ptp_dpaa2->clock = ptp_clock_register(&ptp_dpaa2->caps, dev);
	if (IS_ERR(ptp_dpaa2->clock)) {
		err = PTR_ERR(ptp_dpaa2->clock);
		goto err_close;
	}

	dpaa2_phc_index = ptp_clock_index(ptp_dpaa2->clock);

	dev_set_drvdata(dev, ptp_dpaa2);

	return 0;

err_close:
	dprtc_close(mc_dev->mc_io, 0, mc_dev->mc_handle);
err_free_mcp:
	fsl_mc_portal_free(mc_dev->mc_io);
err_exit:
	kfree(ptp_dpaa2);
	dev_set_drvdata(dev, NULL);
	return err;
}