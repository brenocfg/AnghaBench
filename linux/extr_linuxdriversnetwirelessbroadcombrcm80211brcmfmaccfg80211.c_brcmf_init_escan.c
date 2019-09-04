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
struct TYPE_2__ {int /*<<< orphan*/  escan_state; } ;
struct brcmf_cfg80211_info {int /*<<< orphan*/  escan_timeout_work; int /*<<< orphan*/  escan_timeout; TYPE_1__ escan_info; int /*<<< orphan*/  pub; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_E_ESCAN_RESULT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL_ESCAN_STATE_IDLE ; 
 int /*<<< orphan*/  brcmf_cfg80211_escan_handler ; 
 int /*<<< orphan*/  brcmf_cfg80211_escan_timeout_worker ; 
 int /*<<< orphan*/  brcmf_escan_timeout ; 
 int /*<<< orphan*/  brcmf_fweh_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_init_escan(struct brcmf_cfg80211_info *cfg)
{
	brcmf_fweh_register(cfg->pub, BRCMF_E_ESCAN_RESULT,
			    brcmf_cfg80211_escan_handler);
	cfg->escan_info.escan_state = WL_ESCAN_STATE_IDLE;
	/* Init scan_timeout timer */
	timer_setup(&cfg->escan_timeout, brcmf_escan_timeout, 0);
	INIT_WORK(&cfg->escan_timeout_work,
		  brcmf_cfg80211_escan_timeout_worker);
}