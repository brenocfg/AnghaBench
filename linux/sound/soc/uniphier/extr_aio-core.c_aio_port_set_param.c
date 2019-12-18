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
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_5__* swm; TYPE_2__* aio; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {int /*<<< orphan*/  map; } ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ dir; TYPE_4__ iport; TYPE_3__ oport; } ;
struct TYPE_7__ {TYPE_1__* chip; } ;
struct TYPE_6__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPORTMXACLKSEL0EX (int /*<<< orphan*/ ) ; 
 int IPORTMXACLKSEL0EX_ACLKSEL0EX_INTERNAL ; 
 int /*<<< orphan*/  IPORTMXEXNOE (int /*<<< orphan*/ ) ; 
 int IPORTMXEXNOE_PCMINOE_INPUT ; 
 int /*<<< orphan*/  OPORTMXCTR3 (int /*<<< orphan*/ ) ; 
 int OPORTMXCTR3_IECTHUR_IECOUT ; 
 int OPORTMXCTR3_PMSEL_PAUSE ; 
 int OPORTMXCTR3_PMSW_MUTE_OFF ; 
 int OPORTMXCTR3_SRCSEL_PCM ; 
 int OPORTMXCTR3_SRCSEL_STREAM ; 
 int OPORTMXCTR3_VALID_PCM ; 
 int OPORTMXCTR3_VALID_STREAM ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 scalar_t__ PORT_TYPE_CONV ; 
 scalar_t__ PORT_TYPE_EVE ; 
 int aio_port_set_ch (struct uniphier_aio_sub*) ; 
 int aio_port_set_clk (struct uniphier_aio_sub*) ; 
 int aio_port_set_fmt (struct uniphier_aio_sub*) ; 
 int aio_port_set_rate (struct uniphier_aio_sub*,unsigned int) ; 
 unsigned int params_rate (struct snd_pcm_hw_params const*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_port_set_param(struct uniphier_aio_sub *sub, int pass_through,
		       const struct snd_pcm_hw_params *params)
{
	struct regmap *r = sub->aio->chip->regmap;
	unsigned int rate;
	u32 v;
	int ret;

	if (!pass_through) {
		if (sub->swm->type == PORT_TYPE_EVE ||
		    sub->swm->type == PORT_TYPE_CONV) {
			rate = 48000;
		} else {
			rate = params_rate(params);
		}

		ret = aio_port_set_ch(sub);
		if (ret)
			return ret;

		ret = aio_port_set_rate(sub, rate);
		if (ret)
			return ret;

		ret = aio_port_set_fmt(sub);
		if (ret)
			return ret;
	}

	ret = aio_port_set_clk(sub);
	if (ret)
		return ret;

	if (sub->swm->dir == PORT_DIR_OUTPUT) {
		if (pass_through)
			v = OPORTMXCTR3_SRCSEL_STREAM |
				OPORTMXCTR3_VALID_STREAM;
		else
			v = OPORTMXCTR3_SRCSEL_PCM |
				OPORTMXCTR3_VALID_PCM;

		v |= OPORTMXCTR3_IECTHUR_IECOUT |
			OPORTMXCTR3_PMSEL_PAUSE |
			OPORTMXCTR3_PMSW_MUTE_OFF;
		regmap_write(r, OPORTMXCTR3(sub->swm->oport.map), v);
	} else {
		regmap_write(r, IPORTMXACLKSEL0EX(sub->swm->iport.map),
			     IPORTMXACLKSEL0EX_ACLKSEL0EX_INTERNAL);
		regmap_write(r, IPORTMXEXNOE(sub->swm->iport.map),
			     IPORTMXEXNOE_PCMINOE_INPUT);
	}

	return 0;
}