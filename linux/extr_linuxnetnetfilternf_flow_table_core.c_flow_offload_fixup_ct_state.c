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
struct nf_conntrack_l4proto {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tcp; } ;
struct nf_conn {unsigned int timeout; TYPE_1__ proto; } ;

/* Variables and functions */
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 unsigned int NF_FLOWTABLE_TCP_PICKUP_TIMEOUT ; 
 unsigned int NF_FLOWTABLE_UDP_PICKUP_TIMEOUT ; 
 struct nf_conntrack_l4proto* __nf_ct_l4proto_find (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flow_offload_fixup_tcp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int nf_ct_protonum (struct nf_conn*) ; 
 unsigned int nfct_time_stamp ; 

__attribute__((used)) static void flow_offload_fixup_ct_state(struct nf_conn *ct)
{
	const struct nf_conntrack_l4proto *l4proto;
	unsigned int timeout;
	int l4num;

	l4num = nf_ct_protonum(ct);
	if (l4num == IPPROTO_TCP)
		flow_offload_fixup_tcp(&ct->proto.tcp);

	l4proto = __nf_ct_l4proto_find(nf_ct_l3num(ct), l4num);
	if (!l4proto)
		return;

	if (l4num == IPPROTO_TCP)
		timeout = NF_FLOWTABLE_TCP_PICKUP_TIMEOUT;
	else if (l4num == IPPROTO_UDP)
		timeout = NF_FLOWTABLE_UDP_PICKUP_TIMEOUT;
	else
		return;

	ct->timeout = nfct_time_stamp + timeout;
}