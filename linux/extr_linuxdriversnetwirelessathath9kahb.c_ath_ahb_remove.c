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
struct platform_device {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int /*<<< orphan*/  hw; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_deinit_device (struct ath_softc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ath_softc*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ath_ahb_remove(struct platform_device *pdev)
{
	struct ieee80211_hw *hw = platform_get_drvdata(pdev);

	if (hw) {
		struct ath_softc *sc = hw->priv;

		ath9k_deinit_device(sc);
		free_irq(sc->irq, sc);
		ieee80211_free_hw(sc->hw);
	}

	return 0;
}