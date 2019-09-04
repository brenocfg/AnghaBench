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
struct ieee80211_local {int dummy; } ;
struct ieee80211_chanctx {int dummy; } ;

/* Variables and functions */
 int ieee80211_chanctx_num_assigned (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int ieee80211_chanctx_num_reserved (struct ieee80211_local*,struct ieee80211_chanctx*) ; 

int ieee80211_chanctx_refcount(struct ieee80211_local *local,
			       struct ieee80211_chanctx *ctx)
{
	return ieee80211_chanctx_num_assigned(local, ctx) +
	       ieee80211_chanctx_num_reserved(local, ctx);
}