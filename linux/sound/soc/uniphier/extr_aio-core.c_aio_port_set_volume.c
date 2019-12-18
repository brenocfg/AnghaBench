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
struct uniphier_aio_sub {int /*<<< orphan*/  params; TYPE_4__* swm; TYPE_2__* aio; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int map; } ;
struct TYPE_8__ {scalar_t__ dir; TYPE_3__ oport; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AOUTFADECTR0 ; 
 int AUD_VOL_FADE_TIME ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  OPORTMXTYVOLPARA1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPORTMXTYVOLPARA1_SLOPEU_MASK ; 
 int /*<<< orphan*/  OPORTMXTYVOLPARA2 (int,int /*<<< orphan*/ ) ; 
 int OPORTMXTYVOLPARA2_FADE_FADEIN ; 
 int OPORTMXTYVOLPARA2_FADE_FADEOUT ; 
 int /*<<< orphan*/  OPORTMXTYVOLPARA2_FADE_MASK ; 
 int /*<<< orphan*/  OPORTMXTYVOLPARA2_TARGET_MASK ; 
 scalar_t__ PORT_DIR_INPUT ; 
 int abs (int) ; 
 int aio_port_get_volume (struct uniphier_aio_sub*) ; 
 int max (int,int) ; 
 int params_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void aio_port_set_volume(struct uniphier_aio_sub *sub, int vol)
{
	struct regmap *r = sub->aio->chip->regmap;
	int oport_map = sub->swm->oport.map;
	int cur, diff, slope = 0, fs;

	if (sub->swm->dir == PORT_DIR_INPUT)
		return;

	cur = aio_port_get_volume(sub);
	diff = abs(vol - cur);
	fs = params_rate(&sub->params);
	if (fs)
		slope = diff / AUD_VOL_FADE_TIME * 1000 / fs;
	slope = max(1, slope);

	regmap_update_bits(r, OPORTMXTYVOLPARA1(oport_map, 0),
			   OPORTMXTYVOLPARA1_SLOPEU_MASK, slope << 16);
	regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
			   OPORTMXTYVOLPARA2_TARGET_MASK, vol);

	if (cur < vol)
		regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
				   OPORTMXTYVOLPARA2_FADE_MASK,
				   OPORTMXTYVOLPARA2_FADE_FADEIN);
	else
		regmap_update_bits(r, OPORTMXTYVOLPARA2(oport_map, 0),
				   OPORTMXTYVOLPARA2_FADE_MASK,
				   OPORTMXTYVOLPARA2_FADE_FADEOUT);

	regmap_write(r, AOUTFADECTR0, BIT(oport_map));
}