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
struct wlcore_platdev_data {TYPE_1__* family; } ;
struct wl18xx_priv {int /*<<< orphan*/  conf; } ;
struct wl1271 {int /*<<< orphan*/  conf; struct wl18xx_priv* priv; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cfg_name; } ;

/* Variables and functions */
 struct wlcore_platdev_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*) ; 
 int /*<<< orphan*/  wl18xx_conf ; 
 int /*<<< orphan*/  wl18xx_default_priv_conf ; 
 scalar_t__ wl18xx_load_conf_file (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl18xx_conf_init(struct wl1271 *wl, struct device *dev)
{
	struct platform_device *pdev = wl->pdev;
	struct wlcore_platdev_data *pdata = dev_get_platdata(&pdev->dev);
	struct wl18xx_priv *priv = wl->priv;

	if (wl18xx_load_conf_file(dev, &wl->conf, &priv->conf,
				  pdata->family->cfg_name) < 0) {
		wl1271_warning("falling back to default config");

		/* apply driver default configuration */
		memcpy(&wl->conf, &wl18xx_conf, sizeof(wl->conf));
		/* apply default private configuration */
		memcpy(&priv->conf, &wl18xx_default_priv_conf,
		       sizeof(priv->conf));
	}

	return 0;
}