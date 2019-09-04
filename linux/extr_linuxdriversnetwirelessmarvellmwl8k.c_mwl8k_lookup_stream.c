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
typedef  scalar_t__ u8 ;
struct mwl8k_priv {struct mwl8k_ampdu_stream* ampdu; } ;
struct mwl8k_ampdu_stream {scalar_t__ state; scalar_t__ tid; TYPE_1__* sta; } ;
struct ieee80211_hw {struct mwl8k_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ AMPDU_NO_STREAM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int MWL8K_NUM_AMPDU_STREAMS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mwl8k_ampdu_stream *
mwl8k_lookup_stream(struct ieee80211_hw *hw, u8 *addr, u8 tid)
{
	struct mwl8k_priv *priv = hw->priv;
	int i;

	for (i = 0; i < MWL8K_NUM_AMPDU_STREAMS; i++) {
		struct mwl8k_ampdu_stream *stream;
		stream = &priv->ampdu[i];
		if (stream->state == AMPDU_NO_STREAM)
			continue;
		if (!memcmp(stream->sta->addr, addr, ETH_ALEN) &&
		    stream->tid == tid)
			return stream;
	}
	return NULL;
}