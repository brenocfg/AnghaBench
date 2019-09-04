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
struct macsec_eth_header {int dummy; } ;

/* Variables and functions */
 scalar_t__ skb_mac_header (struct sk_buff*) ; 

__attribute__((used)) static struct macsec_eth_header *macsec_ethhdr(struct sk_buff *skb)
{
	return (struct macsec_eth_header *)skb_mac_header(skb);
}