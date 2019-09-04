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
struct sk_buff {int dummy; } ;
struct iphdr {int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  _iph ;

/* Variables and functions */
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iphdr* skb_header_pointer (struct sk_buff*,int /*<<< orphan*/ ,int,struct iphdr*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 

__attribute__((used)) static bool audit_ip4(struct audit_buffer *ab, struct sk_buff *skb)
{
	struct iphdr _iph;
	const struct iphdr *ih;

	ih = skb_header_pointer(skb, skb_network_offset(skb), sizeof(_iph), &_iph);
	if (!ih)
		return false;

	audit_log_format(ab, " saddr=%pI4 daddr=%pI4 proto=%hhu",
			 &ih->saddr, &ih->daddr, ih->protocol);

	return true;
}