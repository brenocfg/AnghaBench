#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_card {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {void* codec_of_node; void* cpu_of_node; void* platform_of_node; } ;

/* Variables and functions */
 struct snd_soc_card a370db ; 
 TYPE_2__* a370db_dai ; 
 int devm_snd_soc_register_card (TYPE_1__*,struct snd_soc_card*) ; 
 void* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int a370db_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &a370db;

	card->dev = &pdev->dev;

	a370db_dai[0].cpu_of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-controller", 0);
	a370db_dai[0].platform_of_node = a370db_dai[0].cpu_of_node;

	a370db_dai[0].codec_of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 0);

	a370db_dai[1].cpu_of_node = a370db_dai[0].cpu_of_node;
	a370db_dai[1].platform_of_node = a370db_dai[0].cpu_of_node;

	a370db_dai[1].codec_of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 1);

	a370db_dai[2].cpu_of_node = a370db_dai[0].cpu_of_node;
	a370db_dai[2].platform_of_node = a370db_dai[0].cpu_of_node;

	a370db_dai[2].codec_of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 2);

	return devm_snd_soc_register_card(card->dev, card);
}