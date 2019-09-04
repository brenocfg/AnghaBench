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
struct mwl8k_ampdu_stream {int /*<<< orphan*/  tid; TYPE_1__* sta; } ;
struct ieee80211_hw {int /*<<< orphan*/  wiphy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mwl8k_ampdu_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl8k_remove_stream(struct ieee80211_hw *hw, struct mwl8k_ampdu_stream *stream)
{
	wiphy_debug(hw->wiphy, "Remove stream for %pM %d\n", stream->sta->addr,
		    stream->tid);
	memset(stream, 0, sizeof(*stream));
}