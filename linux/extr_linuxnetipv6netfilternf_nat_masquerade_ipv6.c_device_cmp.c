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
struct nf_conn_nat {int masq_index; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_IPV6 ; 
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn*) ; 

__attribute__((used)) static int device_cmp(struct nf_conn *ct, void *ifindex)
{
	const struct nf_conn_nat *nat = nfct_nat(ct);

	if (!nat)
		return 0;
	if (nf_ct_l3num(ct) != NFPROTO_IPV6)
		return 0;
	return nat->masq_index == (int)(long)ifindex;
}