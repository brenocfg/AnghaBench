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
typedef  int /*<<< orphan*/  uint16_t ;
struct udphdr {scalar_t__ len; } ;
struct iphdr {int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_UDP ; 
 unsigned long add_csum_hword (void*,int) ; 
 int /*<<< orphan*/  build_ip_csum (void*,int,unsigned long) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t build_udp_v4_csum(const struct iphdr *iph,
				  const struct udphdr *udph,
				  int num_words)
{
	unsigned long pseudo_sum;
	int num_u16 = sizeof(iph->saddr);	/* halfwords: twice byte len */

	pseudo_sum = add_csum_hword((void *) &iph->saddr, num_u16);
	pseudo_sum += htons(IPPROTO_UDP);
	pseudo_sum += udph->len;
	return build_ip_csum((void *) udph, num_words, pseudo_sum);
}