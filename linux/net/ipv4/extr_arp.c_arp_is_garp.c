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
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARPOP_REPLY ; 
 int RTN_UNICAST ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int inet_addr_type_dev_table (struct net*,struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool arp_is_garp(struct net *net, struct net_device *dev,
			int *addr_type, __be16 ar_op,
			__be32 sip, __be32 tip,
			unsigned char *sha, unsigned char *tha)
{
	bool is_garp = tip == sip;

	/* Gratuitous ARP _replies_ also require target hwaddr to be
	 * the same as source.
	 */
	if (is_garp && ar_op == htons(ARPOP_REPLY))
		is_garp =
			/* IPv4 over IEEE 1394 doesn't provide target
			 * hardware address field in its ARP payload.
			 */
			tha &&
			!memcmp(tha, sha, dev->addr_len);

	if (is_garp) {
		*addr_type = inet_addr_type_dev_table(net, dev, sip);
		if (*addr_type != RTN_UNICAST)
			is_garp = false;
	}
	return is_garp;
}