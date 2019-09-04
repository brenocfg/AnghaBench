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
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDP_FRAME_HEADROOM ; 
 scalar_t__ FDP_FRAME_TAILROOM ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void fdp_nci_i2c_remove_len_lrc(struct sk_buff *skb)
{
	skb_pull(skb, FDP_FRAME_HEADROOM);
	skb_trim(skb, skb->len - FDP_FRAME_TAILROOM);
}