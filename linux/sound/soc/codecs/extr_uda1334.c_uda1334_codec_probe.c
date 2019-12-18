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
struct uda1334_priv {void* deemph; void* mute; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 void* devm_gpiod_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct uda1334_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uda1334_priv*) ; 
 int /*<<< orphan*/  soc_component_dev_uda1334 ; 
 int /*<<< orphan*/  uda1334_dai ; 

__attribute__((used)) static int uda1334_codec_probe(struct platform_device *pdev)
{
	struct uda1334_priv *uda1334;
	int ret;

	uda1334 = devm_kzalloc(&pdev->dev, sizeof(struct uda1334_priv),
			       GFP_KERNEL);
	if (!uda1334)
		return -ENOMEM;

	platform_set_drvdata(pdev, uda1334);

	uda1334->mute = devm_gpiod_get(&pdev->dev, "nxp,mute", GPIOD_OUT_LOW);
	if (IS_ERR(uda1334->mute)) {
		ret = PTR_ERR(uda1334->mute);
		dev_err(&pdev->dev, "Failed to get mute line: %d\n", ret);
		return ret;
	}

	uda1334->deemph = devm_gpiod_get(&pdev->dev, "nxp,deemph", GPIOD_OUT_LOW);
	if (IS_ERR(uda1334->deemph)) {
		ret = PTR_ERR(uda1334->deemph);
		dev_err(&pdev->dev, "Failed to get deemph line: %d\n", ret);
		return ret;
	}

	ret = devm_snd_soc_register_component(&pdev->dev,
					      &soc_component_dev_uda1334,
					      &uda1334_dai, 1);
	if (ret < 0)
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);

	return ret;
}