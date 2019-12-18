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
struct cx2072x_priv {int /*<<< orphan*/  regmap; struct snd_soc_component* codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX2072X_AFG_POWER_STATE ; 
 int /*<<< orphan*/  CX2072X_DIGITAL_BIOS_TEST2 ; 
 int /*<<< orphan*/  CX2072X_PORTC_PIN_CTRL ; 
 int /*<<< orphan*/  cx2072x_reg_init ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cx2072x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cx2072x_probe(struct snd_soc_component *codec)
{
	struct cx2072x_priv *cx2072x = snd_soc_component_get_drvdata(codec);

	cx2072x->codec = codec;

	/*
	 * FIXME: below is, again, a very platform-specific init sequence,
	 * but we keep the code here just for simplicity.  It seems that all
	 * existing hardware implementations require this, so there is no very
	 * much reason to move this out of the codec driver to the platform
	 * data.
	 * But of course it's no "right" thing; if you are a good boy, don't
	 * read and follow the code like this!
	 */
	pm_runtime_get_sync(codec->dev);
	regmap_write(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 0);

	regmap_multi_reg_write(cx2072x->regmap, cx2072x_reg_init,
			       ARRAY_SIZE(cx2072x_reg_init));

	/* configre PortC as input device */
	regmap_update_bits(cx2072x->regmap, CX2072X_PORTC_PIN_CTRL,
			   0x20, 0x20);

	regmap_update_bits(cx2072x->regmap, CX2072X_DIGITAL_BIOS_TEST2,
			   0x84, 0xff);

	regmap_write(cx2072x->regmap, CX2072X_AFG_POWER_STATE, 3);
	pm_runtime_put(codec->dev);

	return 0;
}