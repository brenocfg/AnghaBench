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
struct samsung_i2s_priv {struct platform_device* pdev_sec; TYPE_1__* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  driver_override; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int device_attach (int /*<<< orphan*/ *) ; 
 char* devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 

__attribute__((used)) static int i2s_create_secondary_device(struct samsung_i2s_priv *priv)
{
	struct platform_device *pdev_sec;
	const char *devname;
	int ret;

	devname = devm_kasprintf(&priv->pdev->dev, GFP_KERNEL, "%s-sec",
				 dev_name(&priv->pdev->dev));
	if (!devname)
		return -ENOMEM;

	pdev_sec = platform_device_alloc(devname, -1);
	if (!pdev_sec)
		return -ENOMEM;

	pdev_sec->driver_override = kstrdup("samsung-i2s", GFP_KERNEL);

	ret = platform_device_add(pdev_sec);
	if (ret < 0) {
		platform_device_put(pdev_sec);
		return ret;
	}

	ret = device_attach(&pdev_sec->dev);
	if (ret <= 0) {
		platform_device_unregister(priv->pdev_sec);
		dev_info(&pdev_sec->dev, "device_attach() failed\n");
		return ret;
	}

	priv->pdev_sec = pdev_sec;

	return 0;
}