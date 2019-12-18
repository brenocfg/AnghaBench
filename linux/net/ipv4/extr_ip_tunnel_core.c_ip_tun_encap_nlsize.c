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
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int nla_total_size (int) ; 
 int nla_total_size_64bit (int) ; 

__attribute__((used)) static int ip_tun_encap_nlsize(struct lwtunnel_state *lwtstate)
{
	return nla_total_size_64bit(8)	/* LWTUNNEL_IP_ID */
		+ nla_total_size(4)	/* LWTUNNEL_IP_DST */
		+ nla_total_size(4)	/* LWTUNNEL_IP_SRC */
		+ nla_total_size(1)	/* LWTUNNEL_IP_TOS */
		+ nla_total_size(1)	/* LWTUNNEL_IP_TTL */
		+ nla_total_size(2);	/* LWTUNNEL_IP_FLAGS */
}