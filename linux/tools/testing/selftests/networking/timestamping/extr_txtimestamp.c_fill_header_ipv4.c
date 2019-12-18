#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iphdr {int ihl; int version; int ttl; int /*<<< orphan*/  protocol; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {TYPE_1__ sin_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 TYPE_2__ daddr ; 
 int /*<<< orphan*/  memset (struct iphdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fill_header_ipv4(void *p)
{
	struct iphdr *iph = p;

	memset(iph, 0, sizeof(*iph));

	iph->ihl	= 5;
	iph->version	= 4;
	iph->ttl	= 2;
	iph->saddr	= daddr.sin_addr.s_addr;	/* set for udp csum calc */
	iph->daddr	= daddr.sin_addr.s_addr;
	iph->protocol	= IPPROTO_UDP;

	/* kernel writes saddr, csum, len */

	return sizeof(*iph);
}