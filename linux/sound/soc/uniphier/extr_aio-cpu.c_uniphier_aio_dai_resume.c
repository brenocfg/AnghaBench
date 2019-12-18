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
struct uniphier_aio_sub {int /*<<< orphan*/  setting; int /*<<< orphan*/  substream; int /*<<< orphan*/  spec; } ;
struct uniphier_aio {TYPE_1__* chip; struct uniphier_aio_sub* sub; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  num_wup_aios; int /*<<< orphan*/  rst; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aio_chip_init (TYPE_1__*) ; 
 int /*<<< orphan*/  aio_iecout_set_enable (TYPE_1__*,int) ; 
 int aio_init (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aio_port_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  aio_src_reset (struct uniphier_aio_sub*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct uniphier_aio* uniphier_priv (struct snd_soc_dai*) ; 

int uniphier_aio_dai_resume(struct snd_soc_dai *dai)
{
	struct uniphier_aio *aio = uniphier_priv(dai);
	int ret, i;

	if (!aio->chip->active)
		return 0;

	if (!aio->chip->num_wup_aios) {
		ret = clk_prepare_enable(aio->chip->clk);
		if (ret)
			return ret;

		ret = reset_control_deassert(aio->chip->rst);
		if (ret)
			goto err_out_clock;
	}

	aio_iecout_set_enable(aio->chip, true);
	aio_chip_init(aio->chip);

	for (i = 0; i < ARRAY_SIZE(aio->sub); i++) {
		struct uniphier_aio_sub *sub = &aio->sub[i];

		if (!sub->spec || !sub->substream)
			continue;

		ret = aio_init(sub);
		if (ret)
			goto err_out_reset;

		if (!sub->setting)
			continue;

		aio_port_reset(sub);
		aio_src_reset(sub);
	}
	aio->chip->num_wup_aios++;

	return 0;

err_out_reset:
	if (!aio->chip->num_wup_aios)
		reset_control_assert(aio->chip->rst);
err_out_clock:
	if (!aio->chip->num_wup_aios)
		clk_disable_unprepare(aio->chip->clk);

	return ret;
}