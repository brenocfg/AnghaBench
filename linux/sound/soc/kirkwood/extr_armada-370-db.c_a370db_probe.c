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
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_10__ {TYPE_3__* codecs; TYPE_2__* cpus; TYPE_1__* platforms; } ;
struct TYPE_8__ {void* of_node; } ;
struct TYPE_7__ {void* of_node; } ;
struct TYPE_6__ {void* of_node; } ;

/* Variables and functions */
 struct snd_soc_card a370db ; 
 TYPE_5__* a370db_dai ; 
 int devm_snd_soc_register_card (TYPE_4__*,struct snd_soc_card*) ; 
 void* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int a370db_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &a370db;

	card->dev = &pdev->dev;

	a370db_dai[0].cpus->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-controller", 0);
	a370db_dai[0].platforms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[0].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 0);

	a370db_dai[1].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[1].platforms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[1].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 1);

	a370db_dai[2].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[2].platforms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[2].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 2);

	return devm_snd_soc_register_card(card->dev, card);
}