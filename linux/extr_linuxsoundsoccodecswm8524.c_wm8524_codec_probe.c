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
struct wm8524_priv {int /*<<< orphan*/  mute; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct wm8524_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct wm8524_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_wm8524 ; 
 int /*<<< orphan*/  wm8524_dai ; 

__attribute__((used)) static int wm8524_codec_probe(struct platform_device *pdev)
{
	struct wm8524_priv *wm8524;
	int ret;

	wm8524 = devm_kzalloc(&pdev->dev, sizeof(struct wm8524_priv),
						  GFP_KERNEL);
	if (wm8524 == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, wm8524);

	wm8524->mute = devm_gpiod_get(&pdev->dev, "wlf,mute", GPIOD_OUT_LOW);
	if (IS_ERR(wm8524->mute)) {
		ret = PTR_ERR(wm8524->mute);
		dev_err(&pdev->dev, "Failed to get mute line: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&pdev->dev,
			&soc_component_dev_wm8524, &wm8524_dai, 1);
	if (ret < 0)
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);

	return ret;
}