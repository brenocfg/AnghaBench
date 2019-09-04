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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  channel_ie ;

/* Variables and functions */
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  IEEE80211_P2P_ATTR_LISTEN_CHANNEL ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ SOCIAL_CHAN_1 ; 
 scalar_t__ SOCIAL_CHAN_2 ; 
 scalar_t__ SOCIAL_CHAN_3 ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ cfg80211_get_p2p_attr (scalar_t__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static s32 brcmf_p2p_find_listen_channel(const u8 *ie, u32 ie_len)
{
	u8 channel_ie[5];
	s32 listen_channel;
	s32 err;

	err = cfg80211_get_p2p_attr(ie, ie_len,
				    IEEE80211_P2P_ATTR_LISTEN_CHANNEL,
				    channel_ie, sizeof(channel_ie));
	if (err < 0)
		return err;

	/* listen channel subel length format:     */
	/* 3(country) + 1(op. class) + 1(chan num) */
	listen_channel = (s32)channel_ie[3 + 1];

	if (listen_channel == SOCIAL_CHAN_1 ||
	    listen_channel == SOCIAL_CHAN_2 ||
	    listen_channel == SOCIAL_CHAN_3) {
		brcmf_dbg(INFO, "Found my Listen Channel %d\n", listen_channel);
		return listen_channel;
	}

	return -EPERM;
}