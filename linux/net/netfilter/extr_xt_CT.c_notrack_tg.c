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
struct xt_action_param {int dummy; } ;
struct sk_buff {scalar_t__ _nfct; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_UNTRACKED ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
notrack_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	/* Previously seen (loopback)? Ignore. */
	if (skb->_nfct != 0)
		return XT_CONTINUE;

	nf_ct_set(skb, NULL, IP_CT_UNTRACKED);

	return XT_CONTINUE;
}