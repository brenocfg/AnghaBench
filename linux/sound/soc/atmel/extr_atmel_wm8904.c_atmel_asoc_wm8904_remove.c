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
struct snd_soc_dai_link {TYPE_1__* cpus; } ;
struct snd_soc_card {int dummy; } ;
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;

/* Variables and functions */
 struct snd_soc_dai_link atmel_asoc_wm8904_dailink ; 
 int /*<<< orphan*/  atmel_ssc_put_audio (int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 struct snd_soc_card* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  snd_soc_unregister_card (struct snd_soc_card*) ; 

__attribute__((used)) static int atmel_asoc_wm8904_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct snd_soc_dai_link *dailink = &atmel_asoc_wm8904_dailink;
	int id;

	id = of_alias_get_id((struct device_node *)dailink->cpus->of_node, "ssc");

	snd_soc_unregister_card(card);
	atmel_ssc_put_audio(id);

	return 0;
}