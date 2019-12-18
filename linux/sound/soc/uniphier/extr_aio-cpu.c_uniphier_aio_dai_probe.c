#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uniphier_aio_sub {int /*<<< orphan*/  vol; struct uniphier_aio_spec const* spec; int /*<<< orphan*/ * swm; } ;
struct uniphier_aio_spec {int /*<<< orphan*/  swm; } ;
struct uniphier_aio {TYPE_1__* chip; struct uniphier_aio_sub* sub; } ;
struct snd_soc_dai {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int active; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  AUD_VOL_INIT ; 
 int /*<<< orphan*/  aio_chip_init (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_iecout_set_enable (TYPE_1__*,int) ; 
 struct uniphier_aio_spec* find_spec (struct uniphier_aio*,int /*<<< orphan*/ ,int) ; 
 struct uniphier_aio* uniphier_priv (struct snd_soc_dai*) ; 

int uniphier_aio_dai_probe(struct snd_soc_dai *dai)
{
	struct uniphier_aio *aio = uniphier_priv(dai);
	int i;

	for (i = 0; i < ARRAY_SIZE(aio->sub); i++) {
		struct uniphier_aio_sub *sub = &aio->sub[i];
		const struct uniphier_aio_spec *spec;

		spec = find_spec(aio, dai->name, i);
		if (!spec)
			continue;

		sub->swm = &spec->swm;
		sub->spec = spec;

		sub->vol = AUD_VOL_INIT;
	}

	aio_iecout_set_enable(aio->chip, true);
	aio_chip_init(aio->chip);
	aio->chip->active = 1;

	return 0;
}