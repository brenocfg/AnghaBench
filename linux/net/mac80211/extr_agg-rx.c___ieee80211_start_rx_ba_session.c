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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
struct ieee80211_addba_ext_ie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___ieee80211_start_rx_ba_session (struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct ieee80211_addba_ext_ie const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ieee80211_start_rx_ba_session(struct sta_info *sta,
					    u8 dialog_token, u16 timeout,
					    u16 start_seq_num, u16 ba_policy,
					    u16 tid, u16 buf_size, bool tx,
					    bool auto_seq,
					    const struct ieee80211_addba_ext_ie *addbaext)
{
	mutex_lock(&sta->ampdu_mlme.mtx);
	___ieee80211_start_rx_ba_session(sta, dialog_token, timeout,
					 start_seq_num, ba_policy, tid,
					 buf_size, tx, auto_seq, addbaext);
	mutex_unlock(&sta->ampdu_mlme.mtx);
}