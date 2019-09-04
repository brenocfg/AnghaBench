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
typedef  int /*<<< orphan*/  u16 ;
struct iphdr {int ihl; scalar_t__ protocol; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ rmnet_map_get_csum_field (scalar_t__,void*) ; 

__attribute__((used)) static void rmnet_map_complement_ipv4_txporthdr_csum_field(void *iphdr)
{
	struct iphdr *ip4h = (struct iphdr *)iphdr;
	void *txphdr;
	u16 *csum;

	txphdr = iphdr + ip4h->ihl * 4;

	if (ip4h->protocol == IPPROTO_TCP || ip4h->protocol == IPPROTO_UDP) {
		csum = (u16 *)rmnet_map_get_csum_field(ip4h->protocol, txphdr);
		*csum = ~(*csum);
	}
}