#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_component {int dummy; } ;
struct snd_soc_card {int dummy; } ;
struct atmel_classd {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regcache_sync (int /*<<< orphan*/ ) ; 
 struct atmel_classd* snd_soc_card_get_drvdata (struct snd_soc_card*) ; 
 struct snd_soc_card* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int atmel_classd_component_resume(struct snd_soc_component *component)
{
	struct snd_soc_card *card = snd_soc_component_get_drvdata(component);
	struct atmel_classd *dd = snd_soc_card_get_drvdata(card);

	return regcache_sync(dd->regmap);
}