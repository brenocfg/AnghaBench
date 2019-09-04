#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bdw_rt5677_priv {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ bdw_rt5677_card ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct bdw_rt5677_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct bdw_rt5677_priv*) ; 

__attribute__((used)) static int bdw_rt5677_probe(struct platform_device *pdev)
{
	struct bdw_rt5677_priv *bdw_rt5677;

	bdw_rt5677_card.dev = &pdev->dev;

	/* Allocate driver private struct */
	bdw_rt5677 = devm_kzalloc(&pdev->dev, sizeof(struct bdw_rt5677_priv),
		GFP_KERNEL);
	if (!bdw_rt5677) {
		dev_err(&pdev->dev, "Can't allocate bdw_rt5677\n");
		return -ENOMEM;
	}

	snd_soc_card_set_drvdata(&bdw_rt5677_card, bdw_rt5677);

	return devm_snd_soc_register_card(&pdev->dev, &bdw_rt5677_card);
}