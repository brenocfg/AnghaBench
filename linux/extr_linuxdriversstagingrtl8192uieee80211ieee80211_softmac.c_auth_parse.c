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
typedef  int u16 ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct ieee80211_info_element {int dummy; } ;
struct ieee80211_authentication {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*,int) ; 
 int /*<<< orphan*/  MFIE_TYPE_CHALLENGE ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 auth_parse(struct sk_buff *skb, u8 **challenge, int *chlen)
{
	struct ieee80211_authentication *a;
	u8 *t;
	if (skb->len < (sizeof(struct ieee80211_authentication) - sizeof(struct ieee80211_info_element))) {
		IEEE80211_DEBUG_MGMT("invalid len in auth resp: %d\n", skb->len);
		return 0xcafe;
	}
	*challenge = NULL;
	a = (struct ieee80211_authentication *)skb->data;
	if (skb->len > (sizeof(struct ieee80211_authentication) + 3)) {
		t = skb->data + sizeof(struct ieee80211_authentication);

		if (*(t++) == MFIE_TYPE_CHALLENGE) {
			*chlen = *(t++);
			*challenge = kmemdup(t, *chlen, GFP_ATOMIC);
			if (!*challenge)
				return -ENOMEM;
		}
	}

	return le16_to_cpu(a->status);
}