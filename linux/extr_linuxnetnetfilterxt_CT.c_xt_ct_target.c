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
struct sk_buff {scalar_t__ _nfct; } ;
struct TYPE_2__ {int /*<<< orphan*/  use; } ;
struct nf_conn {TYPE_1__ ct_general; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_NEW ; 
 int /*<<< orphan*/  IP_CT_UNTRACKED ; 
 int XT_CONTINUE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_set (struct sk_buff*,struct nf_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xt_ct_target(struct sk_buff *skb, struct nf_conn *ct)
{
	/* Previously seen (loopback)? Ignore. */
	if (skb->_nfct != 0)
		return XT_CONTINUE;

	if (ct) {
		atomic_inc(&ct->ct_general.use);
		nf_ct_set(skb, ct, IP_CT_NEW);
	} else {
		nf_ct_set(skb, ct, IP_CT_UNTRACKED);
	}

	return XT_CONTINUE;
}