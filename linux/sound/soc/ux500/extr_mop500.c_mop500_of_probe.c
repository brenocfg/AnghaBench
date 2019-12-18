#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {TYPE_3__* codecs; TYPE_2__* platforms; TYPE_1__* cpus; } ;
struct TYPE_7__ {int /*<<< orphan*/ * name; struct device_node* of_node; } ;
struct TYPE_6__ {int /*<<< orphan*/ * name; struct device_node* of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/ * dai_name; struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mop500_card ; 
 TYPE_4__* mop500_dai_links ; 
 int /*<<< orphan*/  mop500_of_node_put () ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int) ; 
 int /*<<< orphan*/  snd_soc_of_parse_card_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mop500_of_probe(struct platform_device *pdev,
			   struct device_node *np)
{
	struct device_node *codec_np, *msp_np[2];
	int i;

	msp_np[0] = of_parse_phandle(np, "stericsson,cpu-dai", 0);
	msp_np[1] = of_parse_phandle(np, "stericsson,cpu-dai", 1);
	codec_np  = of_parse_phandle(np, "stericsson,audio-codec", 0);

	if (!(msp_np[0] && msp_np[1] && codec_np)) {
		dev_err(&pdev->dev, "Phandle missing or invalid\n");
		mop500_of_node_put();
		return -EINVAL;
	}

	for (i = 0; i < 2; i++) {
		mop500_dai_links[i].cpus->of_node = msp_np[i];
		mop500_dai_links[i].cpus->dai_name = NULL;
		mop500_dai_links[i].platforms->of_node = msp_np[i];
		mop500_dai_links[i].platforms->name = NULL;
		mop500_dai_links[i].codecs->of_node = codec_np;
		mop500_dai_links[i].codecs->name = NULL;
	}

	snd_soc_of_parse_card_name(&mop500_card, "stericsson,card-name");

	return 0;
}