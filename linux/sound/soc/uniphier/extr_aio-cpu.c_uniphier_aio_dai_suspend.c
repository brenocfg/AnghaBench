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
struct uniphier_aio {TYPE_1__* chip; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; int /*<<< orphan*/  num_wup_aios; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 struct uniphier_aio* uniphier_priv (struct snd_soc_dai*) ; 

int uniphier_aio_dai_suspend(struct snd_soc_dai *dai)
{
	struct uniphier_aio *aio = uniphier_priv(dai);

	aio->chip->num_wup_aios--;
	if (!aio->chip->num_wup_aios) {
		reset_control_assert(aio->chip->rst);
		clk_disable_unprepare(aio->chip->clk);
	}

	return 0;
}