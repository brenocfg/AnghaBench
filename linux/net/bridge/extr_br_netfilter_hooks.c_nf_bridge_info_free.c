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
 int /*<<< orphan*/  SKB_EXT_BRIDGE_NF ; 
 int /*<<< orphan*/  skb_ext_del (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_bridge_info_free(struct sk_buff *skb)
{
	skb_ext_del(skb, SKB_EXT_BRIDGE_NF);
}