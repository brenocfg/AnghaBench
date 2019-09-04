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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned int ieee80211_get_hdrlen_from_buf(const u8 *data, unsigned len)
{
	const struct ieee80211_hdr *hdr = (const struct ieee80211_hdr *)data;
	unsigned int hdrlen;

	if (unlikely(len < 10))
		return 0;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	if (unlikely(hdrlen > len))
		return 0;
	return hdrlen;
}