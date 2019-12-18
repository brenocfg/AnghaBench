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
struct snd_soc_dai_link {TYPE_3__* codecs; TYPE_2__* cpus; TYPE_1__* platforms; } ;
struct snd_soc_card {TYPE_4__* dev; struct snd_soc_dai_link* dai_link; } ;
struct device_node {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct TYPE_7__ {void* of_node; } ;
struct TYPE_6__ {void* of_node; } ;
struct TYPE_5__ {void* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int storm_parse_of(struct snd_soc_card *card)
{
	struct snd_soc_dai_link *dai_link = card->dai_link;
	struct device_node *np = card->dev->of_node;

	dai_link->cpus->of_node = of_parse_phandle(np, "cpu", 0);
	if (!dai_link->cpus->of_node) {
		dev_err(card->dev, "error getting cpu phandle\n");
		return -EINVAL;
	}
	dai_link->platforms->of_node = dai_link->cpus->of_node;

	dai_link->codecs->of_node = of_parse_phandle(np, "codec", 0);
	if (!dai_link->codecs->of_node) {
		dev_err(card->dev, "error getting codec phandle\n");
		return -EINVAL;
	}

	return 0;
}