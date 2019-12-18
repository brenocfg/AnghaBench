#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct nf_nat_range2 {union nf_inet_addr max_addr; union nf_inet_addr min_addr; int /*<<< orphan*/  flags; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
struct TYPE_6__ {union nf_inet_addr u3; } ;
struct TYPE_5__ {union nf_inet_addr u3; } ;
struct TYPE_7__ {TYPE_2__ src; TYPE_1__ dst; } ;
struct TYPE_8__ {TYPE_3__ tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_REPLY ; 
 int NF_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  NF_NAT_RANGE_MAP_IPS ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,struct nf_nat_range2*,int) ; 

__attribute__((used)) static unsigned int
__nf_nat_alloc_null_binding(struct nf_conn *ct, enum nf_nat_manip_type manip)
{
	/* Force range to this IP; let proto decide mapping for
	 * per-proto parts (hence not IP_NAT_RANGE_PROTO_SPECIFIED).
	 * Use reply in case it's already been mangled (eg local packet).
	 */
	union nf_inet_addr ip =
		(manip == NF_NAT_MANIP_SRC ?
		ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3 :
		ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3);
	struct nf_nat_range2 range = {
		.flags		= NF_NAT_RANGE_MAP_IPS,
		.min_addr	= ip,
		.max_addr	= ip,
	};
	return nf_nat_setup_info(ct, &range, manip);
}