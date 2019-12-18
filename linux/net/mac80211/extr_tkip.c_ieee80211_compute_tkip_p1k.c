#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tkip_ctx {scalar_t__ state; int /*<<< orphan*/  p1k_iv32; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;
struct TYPE_7__ {int /*<<< orphan*/  txlock; struct tkip_ctx tx; } ;
struct TYPE_8__ {TYPE_3__ tkip; } ;
struct TYPE_5__ {int /*<<< orphan*/ * key; } ;
struct ieee80211_key {TYPE_4__ u; TYPE_1__ conf; struct ieee80211_sub_if_data* sdata; } ;

/* Variables and functions */
 size_t NL80211_TKIP_DATA_OFFSET_ENCR_KEY ; 
 scalar_t__ TKIP_STATE_NOT_INIT ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tkip_mixing_phase1 (int /*<<< orphan*/  const*,struct tkip_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_compute_tkip_p1k(struct ieee80211_key *key, u32 iv32)
{
	struct ieee80211_sub_if_data *sdata = key->sdata;
	struct tkip_ctx *ctx = &key->u.tkip.tx;
	const u8 *tk = &key->conf.key[NL80211_TKIP_DATA_OFFSET_ENCR_KEY];

	lockdep_assert_held(&key->u.tkip.txlock);

	/*
	 * Update the P1K when the IV32 is different from the value it
	 * had when we last computed it (or when not initialised yet).
	 * This might flip-flop back and forth if packets are processed
	 * out-of-order due to the different ACs, but then we have to
	 * just compute the P1K more often.
	 */
	if (ctx->p1k_iv32 != iv32 || ctx->state == TKIP_STATE_NOT_INIT)
		tkip_mixing_phase1(tk, ctx, sdata->vif.addr, iv32);
}