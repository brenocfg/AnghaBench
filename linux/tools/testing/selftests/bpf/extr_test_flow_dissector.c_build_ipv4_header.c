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
typedef  void* uint8_t ;
typedef  void* uint32_t ;
struct iphdr {int ihl; int version; int ttl; int /*<<< orphan*/  check; void* daddr; void* saddr; void* protocol; void* id; void* tot_len; void* tos; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_ip_csum (void*,int,int /*<<< orphan*/ ) ; 
 void* htons (int) ; 

__attribute__((used)) static void build_ipv4_header(void *header, uint8_t proto,
			      uint32_t src, uint32_t dst,
			      int payload_len, uint8_t tos)
{
	struct iphdr *iph = header;

	iph->ihl = 5;
	iph->version = 4;
	iph->tos = tos;
	iph->ttl = 8;
	iph->tot_len = htons(sizeof(*iph) + payload_len);
	iph->id = htons(1337);
	iph->protocol = proto;
	iph->saddr = src;
	iph->daddr = dst;
	iph->check = build_ip_csum((void *) iph, iph->ihl << 1, 0);
}