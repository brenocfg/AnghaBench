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
struct snd_soc_card {int /*<<< orphan*/ * dev; } ;
struct skl_machine_pdata {int dmic_num; } ;
struct platform_device {int /*<<< orphan*/  dev; TYPE_1__* id_entry; } ;
struct kbl_rt5663_private {void* sclk; void* mclk; int /*<<< orphan*/  hdmi_pcm_list; } ;
struct TYPE_2__ {scalar_t__ driver_data; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  constraints_dmic_2ch ; 
 int /*<<< orphan*/  constraints_dmic_channels ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct skl_machine_pdata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct kbl_rt5663_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_snd_soc_register_card (int /*<<< orphan*/ *,struct snd_soc_card*) ; 
 int /*<<< orphan*/ * dmic_constraints ; 
 struct snd_soc_card* kabylake_audio_card ; 
 int /*<<< orphan*/  snd_soc_card_set_drvdata (struct snd_soc_card*,struct kbl_rt5663_private*) ; 

__attribute__((used)) static int kabylake_audio_probe(struct platform_device *pdev)
{
	struct kbl_rt5663_private *ctx;
	struct skl_machine_pdata *pdata;
	int ret;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	kabylake_audio_card =
		(struct snd_soc_card *)pdev->id_entry->driver_data;

	kabylake_audio_card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(kabylake_audio_card, ctx);

	pdata = dev_get_drvdata(&pdev->dev);
	if (pdata)
		dmic_constraints = pdata->dmic_num == 2 ?
			&constraints_dmic_2ch : &constraints_dmic_channels;

	ctx->mclk = devm_clk_get(&pdev->dev, "ssp1_mclk");
	if (IS_ERR(ctx->mclk)) {
		ret = PTR_ERR(ctx->mclk);
		if (ret == -ENOENT) {
			dev_info(&pdev->dev,
				"Failed to get ssp1_sclk, defer probe\n");
			return -EPROBE_DEFER;
		}

		dev_err(&pdev->dev, "Failed to get ssp1_mclk with err:%d\n",
								ret);
		return ret;
	}

	ctx->sclk = devm_clk_get(&pdev->dev, "ssp1_sclk");
	if (IS_ERR(ctx->sclk)) {
		ret = PTR_ERR(ctx->sclk);
		if (ret == -ENOENT) {
			dev_info(&pdev->dev,
				"Failed to get ssp1_sclk, defer probe\n");
			return -EPROBE_DEFER;
		}

		dev_err(&pdev->dev, "Failed to get ssp1_sclk with err:%d\n",
								ret);
		return ret;
	}

	return devm_snd_soc_register_card(&pdev->dev, kabylake_audio_card);
}