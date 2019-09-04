#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct txpwr_limits {int dummy; } ;
struct ieee80211_channel {int flags; } ;
struct brcms_cm_info {struct brcms_c_info* wlc; } ;
struct brcms_c_info {int /*<<< orphan*/  hw; TYPE_1__* protection; TYPE_5__* pub; } ;
struct TYPE_10__ {TYPE_3__* ieee_hw; } ;
struct TYPE_7__ {struct ieee80211_channel* chan; } ;
struct TYPE_9__ {TYPE_2__ chandef; } ;
struct TYPE_8__ {TYPE_4__ conf; } ;
struct TYPE_6__ {int /*<<< orphan*/  gmode_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  GMODE_LEGACY_B ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_NO_OFDM ; 
 int /*<<< orphan*/  brcms_b_set_chanspec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct txpwr_limits*) ; 
 int /*<<< orphan*/  brcms_c_channel_min_txpower_limits_with_local_constraint (struct brcms_cm_info*,struct txpwr_limits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_channel_reg_limits (struct brcms_cm_info*,int /*<<< orphan*/ ,struct txpwr_limits*) ; 
 int /*<<< orphan*/  brcms_c_set_gmode (struct brcms_c_info*,int /*<<< orphan*/ ,int) ; 

void
brcms_c_channel_set_chanspec(struct brcms_cm_info *wlc_cm, u16 chanspec,
			 u8 local_constraint_qdbm)
{
	struct brcms_c_info *wlc = wlc_cm->wlc;
	struct ieee80211_channel *ch = wlc->pub->ieee_hw->conf.chandef.chan;
	struct txpwr_limits txpwr;

	brcms_c_channel_reg_limits(wlc_cm, chanspec, &txpwr);

	brcms_c_channel_min_txpower_limits_with_local_constraint(
		wlc_cm, &txpwr, local_constraint_qdbm
	);

	/* set or restore gmode as required by regulatory */
	if (ch->flags & IEEE80211_CHAN_NO_OFDM)
		brcms_c_set_gmode(wlc, GMODE_LEGACY_B, false);
	else
		brcms_c_set_gmode(wlc, wlc->protection->gmode_user, false);

	brcms_b_set_chanspec(wlc->hw, chanspec,
			      !!(ch->flags & IEEE80211_CHAN_NO_IR),
			      &txpwr);
}