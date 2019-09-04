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
struct nf_conn_nat {int dummy; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NF_CT_EXT_NAT ; 
 struct nf_conn_nat* nf_ct_ext_add (struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_is_confirmed (struct nf_conn*) ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 

struct nf_conn_nat *nf_ct_nat_ext_add(struct nf_conn *ct)
{
	struct nf_conn_nat *nat = nfct_nat(ct);
	if (nat)
		return nat;

	if (!nf_ct_is_confirmed(ct))
		nat = nf_ct_ext_add(ct, NF_CT_EXT_NAT, GFP_ATOMIC);

	return nat;
}