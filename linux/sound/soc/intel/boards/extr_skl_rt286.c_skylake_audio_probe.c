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
struct skl_rt286_private {int /*<<< orphan*/  hdmi_pcm_list; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct skl_rt286_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ skylake_rt286 ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (TYPE_1__*,struct skl_rt286_private*) ; 

__attribute__((used)) static int skylake_audio_probe(struct platform_device *pdev)
{
	struct skl_rt286_private *ctx;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	skylake_rt286.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&skylake_rt286, ctx);

	return devm_snd_soc_register_card(&pdev->dev, &skylake_rt286);
}