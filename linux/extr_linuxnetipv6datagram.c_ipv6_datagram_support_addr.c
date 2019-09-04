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
struct TYPE_2__ {scalar_t__ ee_origin; } ;
struct sock_exterr_skb {scalar_t__ port; TYPE_1__ ee; } ;

/* Variables and functions */
 scalar_t__ SO_EE_ORIGIN_ICMP ; 
 scalar_t__ SO_EE_ORIGIN_ICMP6 ; 
 scalar_t__ SO_EE_ORIGIN_LOCAL ; 

__attribute__((used)) static inline bool ipv6_datagram_support_addr(struct sock_exterr_skb *serr)
{
	return serr->ee.ee_origin == SO_EE_ORIGIN_ICMP6 ||
	       serr->ee.ee_origin == SO_EE_ORIGIN_ICMP ||
	       serr->ee.ee_origin == SO_EE_ORIGIN_LOCAL || serr->port;
}