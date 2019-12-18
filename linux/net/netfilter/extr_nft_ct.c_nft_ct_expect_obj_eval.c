#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_12__ {void* code; } ;
struct nft_regs {TYPE_6__ verdict; } ;
struct nft_pktinfo {int /*<<< orphan*/  skb; } ;
struct nft_object {int dummy; } ;
struct nft_ct_expect_obj {scalar_t__ l3num; scalar_t__ size; int timeout; int /*<<< orphan*/  dport; int /*<<< orphan*/  l4proto; } ;
struct TYPE_11__ {scalar_t__ expires; } ;
struct nf_conntrack_expect {TYPE_5__ timeout; } ;
struct nf_conn_help {scalar_t__* expecting; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
struct TYPE_8__ {int /*<<< orphan*/  u3; } ;
struct TYPE_7__ {int /*<<< orphan*/  u3; } ;
struct TYPE_9__ {TYPE_2__ dst; TYPE_1__ src; } ;
struct TYPE_10__ {TYPE_3__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int IP_CT_UNTRACKED ; 
 scalar_t__ NFPROTO_INET ; 
 void* NFT_BREAK ; 
 size_t NF_CT_EXPECT_CLASS_DEFAULT ; 
 void* NF_DROP ; 
 scalar_t__ jiffies ; 
 struct nf_conntrack_expect* nf_ct_expect_alloc (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_expect_init (struct nf_conntrack_expect*,size_t,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (int /*<<< orphan*/ ,int*) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ nf_ct_l3num (struct nf_conn*) ; 
 struct nf_conn_help* nfct_help (struct nf_conn*) ; 
 struct nft_ct_expect_obj* nft_obj_data (struct nft_object*) ; 

__attribute__((used)) static void nft_ct_expect_obj_eval(struct nft_object *obj,
				   struct nft_regs *regs,
				   const struct nft_pktinfo *pkt)
{
	const struct nft_ct_expect_obj *priv = nft_obj_data(obj);
	struct nf_conntrack_expect *exp;
	enum ip_conntrack_info ctinfo;
	struct nf_conn_help *help;
	enum ip_conntrack_dir dir;
	u16 l3num = priv->l3num;
	struct nf_conn *ct;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (!ct || ctinfo == IP_CT_UNTRACKED) {
		regs->verdict.code = NFT_BREAK;
		return;
	}
	dir = CTINFO2DIR(ctinfo);

	help = nfct_help(ct);
	if (!help)
		help = nf_ct_helper_ext_add(ct, GFP_ATOMIC);
	if (!help) {
		regs->verdict.code = NF_DROP;
		return;
	}

	if (help->expecting[NF_CT_EXPECT_CLASS_DEFAULT] >= priv->size) {
		regs->verdict.code = NFT_BREAK;
		return;
	}
	if (l3num == NFPROTO_INET)
		l3num = nf_ct_l3num(ct);

	exp = nf_ct_expect_alloc(ct);
	if (exp == NULL) {
		regs->verdict.code = NF_DROP;
		return;
	}
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, l3num,
		          &ct->tuplehash[!dir].tuple.src.u3,
		          &ct->tuplehash[!dir].tuple.dst.u3,
		          priv->l4proto, NULL, &priv->dport);
	exp->timeout.expires = jiffies + priv->timeout * HZ;

	if (nf_ct_expect_related(exp, 0) != 0)
		regs->verdict.code = NF_DROP;
}