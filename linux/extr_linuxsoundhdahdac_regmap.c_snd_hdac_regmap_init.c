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
struct regmap {int dummy; } ;
struct hdac_device {int /*<<< orphan*/  vendor_verbs; struct regmap* regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  hda_regmap_cfg ; 
 struct regmap* regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct hdac_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_array_init (int /*<<< orphan*/ *,int,int) ; 

int snd_hdac_regmap_init(struct hdac_device *codec)
{
	struct regmap *regmap;

	regmap = regmap_init(&codec->dev, NULL, codec, &hda_regmap_cfg);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);
	codec->regmap = regmap;
	snd_array_init(&codec->vendor_verbs, sizeof(unsigned int), 8);
	return 0;
}