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
struct device {int dummy; } ;
struct fsl_mc_device {struct device dev; } ;
struct ethsw_core {int /*<<< orphan*/  dpsw_handle; int /*<<< orphan*/  mc_io; } ;

/* Variables and functions */
 struct ethsw_core* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int dpsw_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethsw_unregister_notifier (struct device*) ; 

__attribute__((used)) static void ethsw_takedown(struct fsl_mc_device *sw_dev)
{
	struct device *dev = &sw_dev->dev;
	struct ethsw_core *ethsw = dev_get_drvdata(dev);
	int err;

	ethsw_unregister_notifier(dev);

	err = dpsw_close(ethsw->mc_io, 0, ethsw->dpsw_handle);
	if (err)
		dev_warn(dev, "dpsw_close err %d\n", err);
}