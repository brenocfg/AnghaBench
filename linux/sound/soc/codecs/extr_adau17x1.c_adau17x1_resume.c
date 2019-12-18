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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct adau {int /*<<< orphan*/  regmap; int /*<<< orphan*/  (* switch_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  regcache_sync (int /*<<< orphan*/ ) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

int adau17x1_resume(struct snd_soc_component *component)
{
	struct adau *adau = snd_soc_component_get_drvdata(component);

	if (adau->switch_mode)
		adau->switch_mode(component->dev);

	regcache_sync(adau->regmap);

	return 0;
}