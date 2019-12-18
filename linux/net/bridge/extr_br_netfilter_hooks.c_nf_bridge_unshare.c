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
struct nf_bridge_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKB_EXT_BRIDGE_NF ; 
 struct nf_bridge_info* skb_ext_add (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct nf_bridge_info *nf_bridge_unshare(struct sk_buff *skb)
{
	return skb_ext_add(skb, SKB_EXT_BRIDGE_NF);
}