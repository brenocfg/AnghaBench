#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct nf_nat_pptp {int /*<<< orphan*/  pac_call_id; int /*<<< orphan*/  pns_call_id; } ;
struct nf_ct_pptp_master {int /*<<< orphan*/  pns_call_id; int /*<<< orphan*/  pac_call_id; } ;
struct TYPE_18__ {int /*<<< orphan*/  key; } ;
struct TYPE_19__ {TYPE_7__ gre; } ;
struct TYPE_20__ {TYPE_8__ u; } ;
struct TYPE_15__ {int /*<<< orphan*/  key; } ;
struct TYPE_16__ {TYPE_4__ gre; } ;
struct TYPE_17__ {TYPE_5__ u; } ;
struct TYPE_11__ {TYPE_9__ dst; TYPE_6__ src; } ;
struct TYPE_13__ {int /*<<< orphan*/  key; } ;
struct TYPE_14__ {TYPE_2__ gre; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  dir; TYPE_10__ tuple; TYPE_3__ saved_proto; struct nf_conn* master; } ;
struct TYPE_12__ {struct nf_nat_pptp nat_pptp_info; } ;
struct nf_conn_nat {TYPE_1__ help; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  IP_CT_DIR_REPLY ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct nf_ct_pptp_master* nfct_help_data (struct nf_conn const*) ; 
 struct nf_conn_nat* nfct_nat (struct nf_conn const*) ; 

__attribute__((used)) static void
pptp_exp_gre(struct nf_conntrack_expect *expect_orig,
	     struct nf_conntrack_expect *expect_reply)
{
	const struct nf_conn *ct = expect_orig->master;
	struct nf_conn_nat *nat = nfct_nat(ct);
	struct nf_ct_pptp_master *ct_pptp_info;
	struct nf_nat_pptp *nat_pptp_info;

	if (WARN_ON_ONCE(!nat))
		return;

	nat_pptp_info = &nat->help.nat_pptp_info;
	ct_pptp_info = nfct_help_data(ct);

	/* save original PAC call ID in nat_info */
	nat_pptp_info->pac_call_id = ct_pptp_info->pac_call_id;

	/* alter expectation for PNS->PAC direction */
	expect_orig->saved_proto.gre.key = ct_pptp_info->pns_call_id;
	expect_orig->tuple.src.u.gre.key = nat_pptp_info->pns_call_id;
	expect_orig->tuple.dst.u.gre.key = ct_pptp_info->pac_call_id;
	expect_orig->dir = IP_CT_DIR_ORIGINAL;

	/* alter expectation for PAC->PNS direction */
	expect_reply->saved_proto.gre.key = nat_pptp_info->pns_call_id;
	expect_reply->tuple.src.u.gre.key = nat_pptp_info->pac_call_id;
	expect_reply->tuple.dst.u.gre.key = ct_pptp_info->pns_call_id;
	expect_reply->dir = IP_CT_DIR_REPLY;
}