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
struct wm9705_priv {int /*<<< orphan*/  mfd_pdata; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ *) ; 
 struct wm9705_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm9705_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm9705 ; 
 int /*<<< orphan*/  wm9705_dai ; 

__attribute__((used)) static int wm9705_probe(struct platform_device *pdev)
{
	struct wm9705_priv *wm9705;

	wm9705 = devm_kzalloc(&pdev->dev, sizeof(*wm9705), GFP_KERNEL);
	if (wm9705 == NULL)
		return -ENOMEM;

	wm9705->mfd_pdata = dev_get_platdata(&pdev->dev);
	platform_set_drvdata(pdev, wm9705);

	return devm_snd_soc_register_component(&pdev->dev,
			&soc_component_dev_wm9705, wm9705_dai, ARRAY_SIZE(wm9705_dai));
}