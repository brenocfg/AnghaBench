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
struct ath_common {int /*<<< orphan*/  curaid; int /*<<< orphan*/  curbssid; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_write_associd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_htc_set_bssid(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);

	ath9k_hw_write_associd(priv->ah);
	ath_dbg(common, CONFIG, "BSSID: %pM aid: 0x%x\n",
		common->curbssid, common->curaid);
}