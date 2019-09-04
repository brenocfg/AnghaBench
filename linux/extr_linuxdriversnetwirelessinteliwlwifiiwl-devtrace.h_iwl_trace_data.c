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
struct sk_buff {int len; scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAE ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool iwl_trace_data(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (void *)skb->data;
	__le16 fc = hdr->frame_control;
	int offs = 24; /* start with normal header length */

	if (!ieee80211_is_data(fc))
		return false;

	/* Try to determine if the frame is EAPOL. This might have false
	 * positives (if there's no RFC 1042 header and we compare to some
	 * payload instead) but since we're only doing tracing that's not
	 * a problem.
	 */

	if (ieee80211_has_a4(fc))
		offs += 6;
	if (ieee80211_is_data_qos(fc))
		offs += 2;
	/* don't account for crypto - these are unencrypted */

	/* also account for the RFC 1042 header, of course */
	offs += 6;

	return skb->len <= offs + 2 ||
		*(__be16 *)(skb->data + offs) != cpu_to_be16(ETH_P_PAE);
}