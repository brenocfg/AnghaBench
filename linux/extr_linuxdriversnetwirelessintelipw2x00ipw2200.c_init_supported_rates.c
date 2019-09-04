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
struct ipw_supported_rates {void* purpose; int /*<<< orphan*/  ieee_mode; } ;
struct ipw_priv {TYPE_1__* ieee; } ;
struct TYPE_2__ {int freq_band; int modulation; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_A_MODE ; 
 int /*<<< orphan*/  IPW_G_MODE ; 
 void* IPW_RATE_CAPABILITIES ; 
#define  LIBIPW_52GHZ_BAND 128 
 int /*<<< orphan*/  LIBIPW_CCK_DEFAULT_RATES_MASK ; 
 int /*<<< orphan*/  LIBIPW_CCK_MODULATION ; 
 int /*<<< orphan*/  LIBIPW_OFDM_DEFAULT_RATES_MASK ; 
 int LIBIPW_OFDM_MODULATION ; 
 int /*<<< orphan*/  ipw_add_cck_scan_rates (struct ipw_supported_rates*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_add_ofdm_scan_rates (struct ipw_supported_rates*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ipw_supported_rates*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_supported_rates(struct ipw_priv *priv,
				struct ipw_supported_rates *rates)
{
	/* TODO: Mask out rates based on priv->rates_mask */

	memset(rates, 0, sizeof(*rates));
	/* configure supported rates */
	switch (priv->ieee->freq_band) {
	case LIBIPW_52GHZ_BAND:
		rates->ieee_mode = IPW_A_MODE;
		rates->purpose = IPW_RATE_CAPABILITIES;
		ipw_add_ofdm_scan_rates(rates, LIBIPW_CCK_MODULATION,
					LIBIPW_OFDM_DEFAULT_RATES_MASK);
		break;

	default:		/* Mixed or 2.4Ghz */
		rates->ieee_mode = IPW_G_MODE;
		rates->purpose = IPW_RATE_CAPABILITIES;
		ipw_add_cck_scan_rates(rates, LIBIPW_CCK_MODULATION,
				       LIBIPW_CCK_DEFAULT_RATES_MASK);
		if (priv->ieee->modulation & LIBIPW_OFDM_MODULATION) {
			ipw_add_ofdm_scan_rates(rates, LIBIPW_CCK_MODULATION,
						LIBIPW_OFDM_DEFAULT_RATES_MASK);
		}
		break;
	}

	return 0;
}