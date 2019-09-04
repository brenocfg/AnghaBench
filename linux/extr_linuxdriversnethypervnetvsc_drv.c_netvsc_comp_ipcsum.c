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
struct sk_buff {scalar_t__ data; } ;
struct iphdr {int /*<<< orphan*/  ihl; scalar_t__ check; } ;

/* Variables and functions */
 scalar_t__ ip_fast_csum (struct iphdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netvsc_comp_ipcsum(struct sk_buff *skb)
{
	struct iphdr *iph = (struct iphdr *)skb->data;

	iph->check = 0;
	iph->check = ip_fast_csum(iph, iph->ihl);
}