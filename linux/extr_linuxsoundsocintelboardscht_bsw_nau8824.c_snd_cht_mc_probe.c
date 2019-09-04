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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct cht_mc_private {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct cht_mc_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 TYPE_1__ snd_soc_card_cht ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct cht_mc_private*) ; 

__attribute__((used)) static int snd_cht_mc_probe(struct platform_device *pdev)
{
	struct cht_mc_private *drv;
	int ret_val;

	drv = devm_kzalloc(&pdev->dev, sizeof(*drv), GFP_KERNEL);
	if (!drv)
		return -ENOMEM;
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	/* register the soc card */
	snd_soc_card_cht.dev = &pdev->dev;
	ret_val = devm_snd_soc_register_card(&pdev->dev, &snd_soc_card_cht);
	if (ret_val) {
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		return ret_val;
	}
	platform_set_drvdata(pdev, &snd_soc_card_cht);

	return ret_val;
}