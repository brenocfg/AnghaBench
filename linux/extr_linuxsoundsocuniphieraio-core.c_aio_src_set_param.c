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
typedef  int u32 ;
struct uniphier_aio_sub {TYPE_4__* swm; TYPE_2__* aio; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct regmap {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;
struct TYPE_8__ {scalar_t__ dir; TYPE_3__ oport; } ;
struct TYPE_6__ {TYPE_1__* chip; } ;
struct TYPE_5__ {struct regmap* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPORTMXRATE_I (int /*<<< orphan*/ ) ; 
 int OPORTMXRATE_I_ACLKSEL_APLLA1 ; 
 int OPORTMXRATE_I_ACLKSEL_APLLA2 ; 
 int OPORTMXRATE_I_ACLKSRC_APLL ; 
 int OPORTMXRATE_I_FSSEL_32 ; 
 int OPORTMXRATE_I_FSSEL_44_1 ; 
 int OPORTMXRATE_I_FSSEL_48 ; 
 int /*<<< orphan*/  OPORTMXRATE_I_LRCKSTP_MASK ; 
 int /*<<< orphan*/  OPORTMXRATE_I_LRCKSTP_START ; 
 int OPORTMXRATE_I_LRCKSTP_STOP ; 
 int OPORTMXRATE_I_MCKSEL_33 ; 
 int OPORTMXRATE_I_MCKSEL_36 ; 
 int /*<<< orphan*/  OPORTMXSRC1CTR (int /*<<< orphan*/ ) ; 
 int OPORTMXSRC1CTR_FSIIPSEL_INNER ; 
 int OPORTMXSRC1CTR_FSISEL_ACLK ; 
 int OPORTMXSRC1CTR_SRCPATH_CALC ; 
 int OPORTMXSRC1CTR_SYNC_ASYNC ; 
 int OPORTMXSRC1CTR_THMODE_SRC ; 
 scalar_t__ PORT_DIR_OUTPUT ; 
 int params_rate (struct snd_pcm_hw_params const*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 

int aio_src_set_param(struct uniphier_aio_sub *sub,
		      const struct snd_pcm_hw_params *params)
{
	struct regmap *r = sub->aio->chip->regmap;
	u32 v;

	if (sub->swm->dir != PORT_DIR_OUTPUT)
		return 0;

	regmap_write(r, OPORTMXSRC1CTR(sub->swm->oport.map),
		     OPORTMXSRC1CTR_THMODE_SRC |
		     OPORTMXSRC1CTR_SRCPATH_CALC |
		     OPORTMXSRC1CTR_SYNC_ASYNC |
		     OPORTMXSRC1CTR_FSIIPSEL_INNER |
		     OPORTMXSRC1CTR_FSISEL_ACLK);

	switch (params_rate(params)) {
	default:
	case 48000:
		v = OPORTMXRATE_I_ACLKSEL_APLLA1 |
			OPORTMXRATE_I_MCKSEL_36 |
			OPORTMXRATE_I_FSSEL_48;
		break;
	case 44100:
		v = OPORTMXRATE_I_ACLKSEL_APLLA2 |
			OPORTMXRATE_I_MCKSEL_33 |
			OPORTMXRATE_I_FSSEL_44_1;
		break;
	case 32000:
		v = OPORTMXRATE_I_ACLKSEL_APLLA1 |
			OPORTMXRATE_I_MCKSEL_36 |
			OPORTMXRATE_I_FSSEL_32;
		break;
	}

	regmap_write(r, OPORTMXRATE_I(sub->swm->oport.map),
		     v | OPORTMXRATE_I_ACLKSRC_APLL |
		     OPORTMXRATE_I_LRCKSTP_STOP);
	regmap_update_bits(r, OPORTMXRATE_I(sub->swm->oport.map),
			   OPORTMXRATE_I_LRCKSTP_MASK,
			   OPORTMXRATE_I_LRCKSTP_START);

	return 0;
}