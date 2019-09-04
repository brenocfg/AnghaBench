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
typedef  int u32 ;
struct imx_usbmisc_data {int index; scalar_t__ disable_oc; int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EINVAL ; 
 int VF610_OVER_CUR_DIS ; 
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usbmisc_vf610_init(struct imx_usbmisc_data *data)
{
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);
	u32 reg;

	/*
	 * Vybrid only has one misc register set, but in two different
	 * areas. These is reflected in two instances of this driver.
	 */
	if (data->index >= 1)
		return -EINVAL;

	if (data->disable_oc) {
		reg = readl(usbmisc->base);
		writel(reg | VF610_OVER_CUR_DIS, usbmisc->base);
	}

	return 0;
}