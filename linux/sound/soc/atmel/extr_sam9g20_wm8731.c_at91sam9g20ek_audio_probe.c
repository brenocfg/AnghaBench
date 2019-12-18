#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_4__* dev; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_10__ {TYPE_3__* platforms; TYPE_2__* cpus; TYPE_1__* codecs; } ;
struct TYPE_8__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;
struct TYPE_7__ {struct device_node* of_node; int /*<<< orphan*/ * dai_name; } ;
struct TYPE_6__ {struct device_node* of_node; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  MCLK_RATE ; 
 int PTR_ERR (struct clk*) ; 
 TYPE_5__ at91sam9g20ek_dai ; 
 int /*<<< orphan*/  atmel_ssc_put_audio (int /*<<< orphan*/ ) ; 
 int atmel_ssc_set_audio (int /*<<< orphan*/ ) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int clk_set_parent (struct clk*,struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 struct clk* mclk ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_card snd_soc_at91sam9g20ek ; 
 int snd_soc_of_parse_audio_routing (struct snd_soc_card*,char*) ; 
 int snd_soc_of_parse_card_name (struct snd_soc_card*,char*) ; 
 int snd_soc_register_card (struct snd_soc_card*) ; 

__attribute__((used)) static int at91sam9g20ek_audio_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device_node *codec_np, *cpu_np;
	struct clk *pllb;
	struct snd_soc_card *card = &snd_soc_at91sam9g20ek;
	int ret;

	if (!np) {
		return -ENODEV;
	}

	ret = atmel_ssc_set_audio(0);
	if (ret) {
		dev_err(&pdev->dev, "ssc channel is not valid\n");
		return -EINVAL;
	}

	/*
	 * Codec MCLK is supplied by PCK0 - set it up.
	 */
	mclk = clk_get(NULL, "pck0");
	if (IS_ERR(mclk)) {
		dev_err(&pdev->dev, "Failed to get MCLK\n");
		ret = PTR_ERR(mclk);
		goto err;
	}

	pllb = clk_get(NULL, "pllb");
	if (IS_ERR(pllb)) {
		dev_err(&pdev->dev, "Failed to get PLLB\n");
		ret = PTR_ERR(pllb);
		goto err_mclk;
	}
	ret = clk_set_parent(mclk, pllb);
	clk_put(pllb);
	if (ret != 0) {
		dev_err(&pdev->dev, "Failed to set MCLK parent\n");
		goto err_mclk;
	}

	clk_set_rate(mclk, MCLK_RATE);

	card->dev = &pdev->dev;

	/* Parse device node info */
	ret = snd_soc_of_parse_card_name(card, "atmel,model");
	if (ret)
		goto err;

	ret = snd_soc_of_parse_audio_routing(card,
		"atmel,audio-routing");
	if (ret)
		goto err;

	/* Parse codec info */
	at91sam9g20ek_dai.codecs->name = NULL;
	codec_np = of_parse_phandle(np, "atmel,audio-codec", 0);
	if (!codec_np) {
		dev_err(&pdev->dev, "codec info missing\n");
		return -EINVAL;
	}
	at91sam9g20ek_dai.codecs->of_node = codec_np;

	/* Parse dai and platform info */
	at91sam9g20ek_dai.cpus->dai_name = NULL;
	at91sam9g20ek_dai.platforms->name = NULL;
	cpu_np = of_parse_phandle(np, "atmel,ssc-controller", 0);
	if (!cpu_np) {
		dev_err(&pdev->dev, "dai and pcm info missing\n");
		return -EINVAL;
	}
	at91sam9g20ek_dai.cpus->of_node = cpu_np;
	at91sam9g20ek_dai.platforms->of_node = cpu_np;

	of_node_put(codec_np);
	of_node_put(cpu_np);

	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card() failed\n");
	}

	return ret;

err_mclk:
	clk_put(mclk);
	mclk = NULL;
err:
	atmel_ssc_put_audio(0);
	return ret;
}