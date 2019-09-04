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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
struct TYPE_2__ {unsigned int timeout; } ;

/* Variables and functions */
 int NF_ACCEPT ; 
 TYPE_1__* generic_pernet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_refresh_acct (struct nf_conn*,int,struct sk_buff const*,unsigned int const) ; 
 unsigned int* nf_ct_timeout_lookup (struct nf_conn*) ; 

__attribute__((used)) static int generic_packet(struct nf_conn *ct,
			  const struct sk_buff *skb,
			  unsigned int dataoff,
			  enum ip_conntrack_info ctinfo)
{
	const unsigned int *timeout = nf_ct_timeout_lookup(ct);

	if (!timeout)
		timeout = &generic_pernet(nf_ct_net(ct))->timeout;

	nf_ct_refresh_acct(ct, ctinfo, skb, *timeout);
	return NF_ACCEPT;
}