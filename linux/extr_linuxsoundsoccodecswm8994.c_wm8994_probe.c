#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wm8994_priv {int /*<<< orphan*/  wm8994; int /*<<< orphan*/  fw_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct wm8994_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm8994_priv*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_idle (TYPE_1__*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8994 ; 
 int /*<<< orphan*/  wm8994_dai ; 

__attribute__((used)) static int wm8994_probe(struct platform_device *pdev)
{
	struct wm8994_priv *wm8994;

	wm8994 = devm_kzalloc(&pdev->dev, sizeof(struct wm8994_priv),
			      GFP_KERNEL);
	if (wm8994 == NULL)
		return -ENOMEM;
	platform_set_drvdata(pdev, wm8994);

	mutex_init(&wm8994->fw_lock);

	wm8994->wm8994 = dev_get_drvdata(pdev->dev.parent);

	pm_runtime_enable(&pdev->dev);
	pm_runtime_idle(&pdev->dev);

	return devm_snd_soc_register_component(&pdev->dev, &soc_component_dev_wm8994,
			wm8994_dai, ARRAY_SIZE(wm8994_dai));
}