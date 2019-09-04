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

/* Variables and functions */
 int /*<<< orphan*/  SKB_GSO_GRE ; 
 int /*<<< orphan*/  SKB_GSO_GRE_CSUM ; 
 int iptunnel_handle_offloads (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gre_handle_offloads(struct sk_buff *skb, bool csum)
{
	return iptunnel_handle_offloads(skb, csum ? SKB_GSO_GRE_CSUM : SKB_GSO_GRE);
}