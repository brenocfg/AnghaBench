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
struct imx_usbmisc_data {int /*<<< orphan*/  dev; } ;
struct imx_usbmisc {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 struct imx_usbmisc* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx53_usbmisc_ops ; 

__attribute__((used)) static inline bool is_imx53_usbmisc(struct imx_usbmisc_data *data)
{
	struct imx_usbmisc *usbmisc = dev_get_drvdata(data->dev);

	return usbmisc->ops == &imx53_usbmisc_ops;
}