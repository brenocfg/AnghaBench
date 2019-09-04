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
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct ieee80211_key_seq {int dummy; } ;
struct ieee80211_key {int /*<<< orphan*/  conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_key_seq ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_key_seq*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  trace_drv_get_key_seq (struct ieee80211_local*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void drv_get_key_seq(struct ieee80211_local *local,
				   struct ieee80211_key *key,
				   struct ieee80211_key_seq *seq)
{
	if (local->ops->get_key_seq)
		local->ops->get_key_seq(&local->hw, &key->conf, seq);
	trace_drv_get_key_seq(local, &key->conf);
}