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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct iphdr {int version; int ihl; int ttl; int /*<<< orphan*/  check; int /*<<< orphan*/  tot_len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; scalar_t__ tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_EGP ; 
 int /*<<< orphan*/  cfg_dst_addr ; 
 int /*<<< orphan*/  cfg_src_addr ; 
 int /*<<< orphan*/  get_ip_csum (void*,int) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct iphdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int setup_iph(struct iphdr *iph, uint16_t payload_len)
{
	struct sockaddr_in *daddr = (void *) &cfg_dst_addr;
	struct sockaddr_in *saddr = (void *) &cfg_src_addr;

	memset(iph, 0, sizeof(*iph));

	iph->version	= 4;
	iph->tos	= 0;
	iph->ihl	= 5;
	iph->ttl	= 2;
	iph->saddr	= saddr->sin_addr.s_addr;
	iph->daddr	= daddr->sin_addr.s_addr;
	iph->protocol	= IPPROTO_EGP;
	iph->tot_len	= htons(sizeof(*iph) + payload_len);
	iph->check	= get_ip_csum((void *) iph, iph->ihl << 1);

	return sizeof(*iph);
}