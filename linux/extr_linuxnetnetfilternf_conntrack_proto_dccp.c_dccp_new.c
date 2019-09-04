#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct sk_buff {int dummy; } ;
struct nf_dccp_net {int /*<<< orphan*/  dccp_loose; } ;
struct TYPE_3__ {size_t* role; size_t state; size_t last_dir; scalar_t__ handshake_seq; int /*<<< orphan*/  last_pkt; } ;
struct TYPE_4__ {TYPE_1__ dccp; } ;
struct nf_conn {TYPE_2__ proto; } ;
struct net {int dummy; } ;
struct dccp_hdr {size_t dccph_type; } ;
typedef  int /*<<< orphan*/  _dh ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
#define  CT_DCCP_INVALID 129 
 size_t CT_DCCP_NONE ; 
#define  CT_DCCP_REQUEST 128 
 size_t CT_DCCP_ROLE_CLIENT ; 
 size_t CT_DCCP_ROLE_SERVER ; 
 int /*<<< orphan*/  DCCP_PKT_REQUEST ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 struct nf_dccp_net* dccp_pernet (struct net*) ; 
 int*** dccp_state_table ; 
 int /*<<< orphan*/  nf_ct_l4proto_log_invalid (struct sk_buff const*,struct nf_conn*,char*,char const*) ; 
 struct net* nf_ct_net (struct nf_conn*) ; 
 struct dccp_hdr* skb_header_pointer (struct sk_buff const*,unsigned int,int,struct dccp_hdr*) ; 

__attribute__((used)) static bool dccp_new(struct nf_conn *ct, const struct sk_buff *skb,
		     unsigned int dataoff)
{
	struct net *net = nf_ct_net(ct);
	struct nf_dccp_net *dn;
	struct dccp_hdr _dh, *dh;
	const char *msg;
	u_int8_t state;

	dh = skb_header_pointer(skb, dataoff, sizeof(_dh), &_dh);
	BUG_ON(dh == NULL);

	state = dccp_state_table[CT_DCCP_ROLE_CLIENT][dh->dccph_type][CT_DCCP_NONE];
	switch (state) {
	default:
		dn = dccp_pernet(net);
		if (dn->dccp_loose == 0) {
			msg = "not picking up existing connection ";
			goto out_invalid;
		}
	case CT_DCCP_REQUEST:
		break;
	case CT_DCCP_INVALID:
		msg = "invalid state transition ";
		goto out_invalid;
	}

	ct->proto.dccp.role[IP_CT_DIR_ORIGINAL] = CT_DCCP_ROLE_CLIENT;
	ct->proto.dccp.role[IP_CT_DIR_REPLY] = CT_DCCP_ROLE_SERVER;
	ct->proto.dccp.state = CT_DCCP_NONE;
	ct->proto.dccp.last_pkt = DCCP_PKT_REQUEST;
	ct->proto.dccp.last_dir = IP_CT_DIR_ORIGINAL;
	ct->proto.dccp.handshake_seq = 0;
	return true;

out_invalid:
	nf_ct_l4proto_log_invalid(skb, ct, "%s", msg);
	return false;
}