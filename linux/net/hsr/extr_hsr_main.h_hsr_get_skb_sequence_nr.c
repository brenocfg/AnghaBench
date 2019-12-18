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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sequence_nr; } ;
struct hsr_ethhdr {TYPE_1__ hsr_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline u16 hsr_get_skb_sequence_nr(struct sk_buff *skb)
{
	struct hsr_ethhdr *hsr_ethhdr;

	hsr_ethhdr = (struct hsr_ethhdr *)skb_mac_header(skb);
	return ntohs(hsr_ethhdr->hsr_tag.sequence_nr);
}