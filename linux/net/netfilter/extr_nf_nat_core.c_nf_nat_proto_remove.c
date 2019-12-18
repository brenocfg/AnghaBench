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
struct nf_nat_proto_clean {scalar_t__ l3proto; scalar_t__ l4proto; } ;
struct nf_conn {int status; } ;

/* Variables and functions */
 int IPS_NAT_MASK ; 
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 
 scalar_t__ nf_ct_protonum (struct nf_conn*) ; 

__attribute__((used)) static int nf_nat_proto_remove(struct nf_conn *i, void *data)
{
	const struct nf_nat_proto_clean *clean = data;

	if ((clean->l3proto && nf_ct_l3num(i) != clean->l3proto) ||
	    (clean->l4proto && nf_ct_protonum(i) != clean->l4proto))
		return 0;

	return i->status & IPS_NAT_MASK ? 1 : 0;
}