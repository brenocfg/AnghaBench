#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xt_conntrack_mtinfo3 {int match_flags; scalar_t__ l4proto; int invert_flags; int /*<<< orphan*/  repldst_port_high; int /*<<< orphan*/  repldst_port; int /*<<< orphan*/  replsrc_port_high; int /*<<< orphan*/  replsrc_port; int /*<<< orphan*/  origdst_port_high; int /*<<< orphan*/  origdst_port; int /*<<< orphan*/  origsrc_port_high; int /*<<< orphan*/  origsrc_port; } ;
struct TYPE_9__ {int /*<<< orphan*/  all; } ;
struct TYPE_10__ {TYPE_4__ u; } ;
struct TYPE_7__ {int /*<<< orphan*/  all; } ;
struct TYPE_8__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_5__ dst; TYPE_3__ src; } ;
struct nf_conn {TYPE_1__* tuplehash; } ;
struct TYPE_6__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 
 size_t IP_CT_DIR_REPLY ; 
 int XT_CONNTRACK_ORIGDST_PORT ; 
 int XT_CONNTRACK_ORIGSRC_PORT ; 
 int XT_CONNTRACK_PROTO ; 
 int XT_CONNTRACK_REPLDST_PORT ; 
 int XT_CONNTRACK_REPLSRC_PORT ; 
 scalar_t__ nf_ct_protonum (struct nf_conn const*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool
ct_proto_port_check_v3(const struct xt_conntrack_mtinfo3 *info,
		       const struct nf_conn *ct)
{
	const struct nf_conntrack_tuple *tuple;

	tuple = &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
	if ((info->match_flags & XT_CONNTRACK_PROTO) &&
	    (nf_ct_protonum(ct) == info->l4proto) ^
	    !(info->invert_flags & XT_CONNTRACK_PROTO))
		return false;

	/* Shortcut to match all recognized protocols by using ->src.all. */
	if ((info->match_flags & XT_CONNTRACK_ORIGSRC_PORT) &&
	    !port_match(info->origsrc_port, info->origsrc_port_high,
			ntohs(tuple->src.u.all),
			info->invert_flags & XT_CONNTRACK_ORIGSRC_PORT))
		return false;

	if ((info->match_flags & XT_CONNTRACK_ORIGDST_PORT) &&
	    !port_match(info->origdst_port, info->origdst_port_high,
			ntohs(tuple->dst.u.all),
			info->invert_flags & XT_CONNTRACK_ORIGDST_PORT))
		return false;

	tuple = &ct->tuplehash[IP_CT_DIR_REPLY].tuple;

	if ((info->match_flags & XT_CONNTRACK_REPLSRC_PORT) &&
	    !port_match(info->replsrc_port, info->replsrc_port_high,
			ntohs(tuple->src.u.all),
			info->invert_flags & XT_CONNTRACK_REPLSRC_PORT))
		return false;

	if ((info->match_flags & XT_CONNTRACK_REPLDST_PORT) &&
	    !port_match(info->repldst_port, info->repldst_port_high,
			ntohs(tuple->dst.u.all),
			info->invert_flags & XT_CONNTRACK_REPLDST_PORT))
		return false;

	return true;
}