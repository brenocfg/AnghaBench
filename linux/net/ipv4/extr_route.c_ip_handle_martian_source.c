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
struct net_device {scalar_t__ hard_header_len; int /*<<< orphan*/  name; } ;
struct in_device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 scalar_t__ IN_DEV_LOG_MARTIANS (struct in_device*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  RT_CACHE_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_martian_src ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_mac_header (struct sk_buff*) ; 
 scalar_t__ skb_mac_header_was_set (struct sk_buff*) ; 

__attribute__((used)) static void ip_handle_martian_source(struct net_device *dev,
				     struct in_device *in_dev,
				     struct sk_buff *skb,
				     __be32 daddr,
				     __be32 saddr)
{
	RT_CACHE_STAT_INC(in_martian_src);
#ifdef CONFIG_IP_ROUTE_VERBOSE
	if (IN_DEV_LOG_MARTIANS(in_dev) && net_ratelimit()) {
		/*
		 *	RFC1812 recommendation, if source is martian,
		 *	the only hint is MAC header.
		 */
		pr_warn("martian source %pI4 from %pI4, on dev %s\n",
			&daddr, &saddr, dev->name);
		if (dev->hard_header_len && skb_mac_header_was_set(skb)) {
			print_hex_dump(KERN_WARNING, "ll header: ",
				       DUMP_PREFIX_OFFSET, 16, 1,
				       skb_mac_header(skb),
				       dev->hard_header_len, false);
		}
	}
#endif
}