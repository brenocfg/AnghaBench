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
struct wm9712_priv {int /*<<< orphan*/  mfd_pdata; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct wm9712_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm9712_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm9712 ; 
 int /*<<< orphan*/  wm9712_dai ; 

__attribute__((used)) static int wm9712_probe(struct platform_device *pdev)
{
	struct wm9712_priv *wm9712;

	wm9712 = devm_kzalloc(&pdev->dev, sizeof(*wm9712), GFP_KERNEL);
	if (wm9712 == NULL)
		return -ENOMEM;

	mutex_init(&wm9712->lock);

	wm9712->mfd_pdata = dev_get_platdata(&pdev->dev);
	platform_set_drvdata(pdev, wm9712);

	return devm_snd_soc_register_component(&pdev->dev,
			&soc_component_dev_wm9712, wm9712_dai, ARRAY_SIZE(wm9712_dai));
}