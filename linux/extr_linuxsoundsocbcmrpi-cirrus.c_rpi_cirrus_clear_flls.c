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
struct snd_soc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_FLL_SRC_NONE ; 
 int /*<<< orphan*/  WM5102_FLL1 ; 
 int /*<<< orphan*/  WM5102_FLL1_REFCLK ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_set_pll (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpi_cirrus_clear_flls(struct snd_soc_card *card,
	struct snd_soc_component *wm5102_component) {

	int ret1, ret2;

	ret1 = snd_soc_component_set_pll(wm5102_component,
		WM5102_FLL1, ARIZONA_FLL_SRC_NONE, 0, 0);
	ret2 = snd_soc_component_set_pll(wm5102_component,
		WM5102_FLL1_REFCLK, ARIZONA_FLL_SRC_NONE, 0, 0);

	if (ret1) {
		dev_warn(card->dev,
			"setting FLL1 to zero failed: %d\n", ret1);
		return ret1;
	}
	if (ret2) {
		dev_warn(card->dev,
			"setting FLL1_REFCLK to zero failed: %d\n", ret2);
		return ret2;
	}
	return 0;
}