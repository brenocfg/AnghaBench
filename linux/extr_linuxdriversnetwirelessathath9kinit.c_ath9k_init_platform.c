#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ath_softc {struct ath_hw* sc_ah; TYPE_1__* dev; } ;
struct TYPE_4__ {int led_active_high; int tx_gain_buffalo; } ;
struct ath_hw {TYPE_2__ config; int /*<<< orphan*/  ah_flags; int /*<<< orphan*/  disable_5ghz; int /*<<< orphan*/  disable_2ghz; int /*<<< orphan*/  external_reset; int /*<<< orphan*/  get_mac_revision; int /*<<< orphan*/  is_clk_25mhz; int /*<<< orphan*/  led_pin; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; } ;
struct ath_common {int /*<<< orphan*/  macaddr; } ;
struct ath9k_platform_data {scalar_t__ macaddr; scalar_t__ tx_gain_buffalo; scalar_t__ led_active_high; scalar_t__ eeprom_name; int /*<<< orphan*/  endian_check; int /*<<< orphan*/  disable_5ghz; int /*<<< orphan*/  disable_2ghz; int /*<<< orphan*/  external_reset; int /*<<< orphan*/  get_mac_revision; int /*<<< orphan*/  is_clk_25mhz; int /*<<< orphan*/  led_pin; int /*<<< orphan*/  gpio_val; int /*<<< orphan*/  gpio_mask; int /*<<< orphan*/  use_eeprom; } ;
struct TYPE_3__ {struct ath9k_platform_data* platform_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_NO_EEP_SWAP ; 
 int /*<<< orphan*/  AH_USE_EEPROM ; 
 int ath9k_eeprom_request (struct ath_softc*,scalar_t__) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ath9k_init_platform(struct ath_softc *sc)
{
	struct ath9k_platform_data *pdata = sc->dev->platform_data;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	int ret;

	if (!pdata)
		return 0;

	if (!pdata->use_eeprom) {
		ah->ah_flags &= ~AH_USE_EEPROM;
		ah->gpio_mask = pdata->gpio_mask;
		ah->gpio_val = pdata->gpio_val;
		ah->led_pin = pdata->led_pin;
		ah->is_clk_25mhz = pdata->is_clk_25mhz;
		ah->get_mac_revision = pdata->get_mac_revision;
		ah->external_reset = pdata->external_reset;
		ah->disable_2ghz = pdata->disable_2ghz;
		ah->disable_5ghz = pdata->disable_5ghz;

		if (!pdata->endian_check)
			ah->ah_flags |= AH_NO_EEP_SWAP;
	}

	if (pdata->eeprom_name) {
		ret = ath9k_eeprom_request(sc, pdata->eeprom_name);
		if (ret)
			return ret;
	}

	if (pdata->led_active_high)
		ah->config.led_active_high = true;

	if (pdata->tx_gain_buffalo)
		ah->config.tx_gain_buffalo = true;

	if (pdata->macaddr)
		ether_addr_copy(common->macaddr, pdata->macaddr);

	return 0;
}