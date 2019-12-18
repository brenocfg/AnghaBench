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
struct iphdr {int /*<<< orphan*/  daddr; } ;
struct ethhdr {int dummy; } ;
struct batadv_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_P_IP ; 
 scalar_t__ batadv_mcast_is_report_ipv4 (struct sk_buff*) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 scalar_t__ ipv4_is_local_multicast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int batadv_mcast_forw_mode_check_ipv4(struct batadv_priv *bat_priv,
					     struct sk_buff *skb,
					     bool *is_unsnoopable,
					     int *is_routable)
{
	struct iphdr *iphdr;

	/* We might fail due to out-of-memory -> drop it */
	if (!pskb_may_pull(skb, sizeof(struct ethhdr) + sizeof(*iphdr)))
		return -ENOMEM;

	if (batadv_mcast_is_report_ipv4(skb))
		return -EINVAL;

	iphdr = ip_hdr(skb);

	/* link-local multicast listeners behind a bridge are
	 * not snoopable (see RFC4541, section 2.1.2.2)
	 */
	if (ipv4_is_local_multicast(iphdr->daddr))
		*is_unsnoopable = true;
	else
		*is_routable = ETH_P_IP;

	return 0;
}