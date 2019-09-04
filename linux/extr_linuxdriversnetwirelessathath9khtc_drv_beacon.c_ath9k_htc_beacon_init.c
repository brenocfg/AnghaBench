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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  sw_beacon_response_time; } ;
struct ath_hw {int /*<<< orphan*/  imask; TYPE_1__ config; } ;
struct ath_beacon_config {int /*<<< orphan*/  intval; int /*<<< orphan*/  nexttbtt; } ;
struct TYPE_4__ {scalar_t__ bmisscnt; } ;
struct ath9k_htc_priv {TYPE_2__ beacon; struct ath_hw* ah; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SWBA_RESPONSE ; 
 int /*<<< orphan*/  MIN_SWBA_RESPONSE ; 
 int /*<<< orphan*/  TU_TO_USEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_CMD_BUF (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WMI_DISABLE_INTR_CMDID ; 
 int /*<<< orphan*/  WMI_ENABLE_INTR_CMDID ; 
 int /*<<< orphan*/  ath9k_htc_beaconq_config (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_hw_beaconinit (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_reset_tsf (struct ath_hw*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_htc_beacon_init(struct ath9k_htc_priv *priv,
				  struct ath_beacon_config *conf,
				  bool reset_tsf)
{
	struct ath_hw *ah = priv->ah;
	int ret __attribute__ ((unused));
	__be32 htc_imask = 0;
	u8 cmd_rsp;

	if (conf->intval >= TU_TO_USEC(DEFAULT_SWBA_RESPONSE))
		ah->config.sw_beacon_response_time = DEFAULT_SWBA_RESPONSE;
	else
		ah->config.sw_beacon_response_time = MIN_SWBA_RESPONSE;

	WMI_CMD(WMI_DISABLE_INTR_CMDID);
	if (reset_tsf)
		ath9k_hw_reset_tsf(ah);
	ath9k_htc_beaconq_config(priv);
	ath9k_hw_beaconinit(ah, conf->nexttbtt, conf->intval);
	priv->beacon.bmisscnt = 0;
	htc_imask = cpu_to_be32(ah->imask);
	WMI_CMD_BUF(WMI_ENABLE_INTR_CMDID, &htc_imask);
}