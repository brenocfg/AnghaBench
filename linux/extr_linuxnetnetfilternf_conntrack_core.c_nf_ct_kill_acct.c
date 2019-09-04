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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_acct_update (struct nf_conn*,int,int /*<<< orphan*/ ) ; 
 int nf_ct_delete (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool nf_ct_kill_acct(struct nf_conn *ct,
		     enum ip_conntrack_info ctinfo,
		     const struct sk_buff *skb)
{
	nf_ct_acct_update(ct, ctinfo, skb->len);

	return nf_ct_delete(ct, 0, 0);
}