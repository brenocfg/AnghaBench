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
struct nf_nat_l3proto {size_t l3proto; } ;

/* Variables and functions */
 size_t IPPROTO_TCP ; 
 size_t IPPROTO_UDP ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,struct nf_nat_l3proto const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_nat_l3protos ; 
 struct nf_nat_l3proto const nf_nat_l4proto_tcp ; 
 struct nf_nat_l3proto const nf_nat_l4proto_udp ; 
 int /*<<< orphan*/ ** nf_nat_l4protos ; 
 int /*<<< orphan*/  nf_nat_proto_mutex ; 

int nf_nat_l3proto_register(const struct nf_nat_l3proto *l3proto)
{
	mutex_lock(&nf_nat_proto_mutex);
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto->l3proto][IPPROTO_TCP],
			 &nf_nat_l4proto_tcp);
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto->l3proto][IPPROTO_UDP],
			 &nf_nat_l4proto_udp);
#ifdef CONFIG_NF_NAT_PROTO_DCCP
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto->l3proto][IPPROTO_DCCP],
			 &nf_nat_l4proto_dccp);
#endif
#ifdef CONFIG_NF_NAT_PROTO_SCTP
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto->l3proto][IPPROTO_SCTP],
			 &nf_nat_l4proto_sctp);
#endif
#ifdef CONFIG_NF_NAT_PROTO_UDPLITE
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto->l3proto][IPPROTO_UDPLITE],
			 &nf_nat_l4proto_udplite);
#endif
	mutex_unlock(&nf_nat_proto_mutex);

	RCU_INIT_POINTER(nf_nat_l3protos[l3proto->l3proto], l3proto);
	return 0;
}