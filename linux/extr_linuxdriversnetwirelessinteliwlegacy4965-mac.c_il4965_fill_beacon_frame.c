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
typedef  int u32 ;
struct il_priv {TYPE_1__* beacon_skb; int /*<<< orphan*/  mutex; } ;
struct ieee80211_hdr {int dummy; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_hdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
il4965_fill_beacon_frame(struct il_priv *il, struct ieee80211_hdr *hdr,
			 int left)
{
	lockdep_assert_held(&il->mutex);

	if (!il->beacon_skb)
		return 0;

	if (il->beacon_skb->len > left)
		return 0;

	memcpy(hdr, il->beacon_skb->data, il->beacon_skb->len);

	return il->beacon_skb->len;
}