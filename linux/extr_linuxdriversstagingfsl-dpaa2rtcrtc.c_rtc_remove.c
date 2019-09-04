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
struct ptp_dpaa2_priv {int /*<<< orphan*/  clock; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  mc_handle; struct device dev; } ;

/* Variables and functions */
 struct ptp_dpaa2_priv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprtc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ptp_dpaa2_priv*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtc_remove(struct fsl_mc_device *mc_dev)
{
	struct ptp_dpaa2_priv *ptp_dpaa2;
	struct device *dev = &mc_dev->dev;

	ptp_dpaa2 = dev_get_drvdata(dev);
	ptp_clock_unregister(ptp_dpaa2->clock);

	dprtc_close(mc_dev->mc_io, 0, mc_dev->mc_handle);
	fsl_mc_portal_free(mc_dev->mc_io);

	kfree(ptp_dpaa2);
	dev_set_drvdata(dev, NULL);

	return 0;
}