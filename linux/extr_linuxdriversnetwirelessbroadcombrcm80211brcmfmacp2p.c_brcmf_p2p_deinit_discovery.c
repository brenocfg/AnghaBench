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
struct brcmf_p2p_info {TYPE_1__* bss_idx; } ;
struct brcmf_cfg80211_vif {int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {struct brcmf_cfg80211_vif* vif; } ;

/* Variables and functions */
 size_t P2PAPI_BSSCFG_DEVICE ; 
 size_t P2PAPI_BSSCFG_PRIMARY ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  WL_P2P_DISC_ST_SCAN ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_fil_iovar_int_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_p2p_set_discover_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 brcmf_p2p_deinit_discovery(struct brcmf_p2p_info *p2p)
{
	struct brcmf_cfg80211_vif *vif;

	brcmf_dbg(TRACE, "enter\n");

	/* Set the discovery state to SCAN */
	vif = p2p->bss_idx[P2PAPI_BSSCFG_DEVICE].vif;
	(void)brcmf_p2p_set_discover_state(vif->ifp, WL_P2P_DISC_ST_SCAN, 0, 0);

	/* Disable P2P discovery in the firmware */
	vif = p2p->bss_idx[P2PAPI_BSSCFG_PRIMARY].vif;
	(void)brcmf_fil_iovar_int_set(vif->ifp, "p2p_disc", 0);

	return 0;
}