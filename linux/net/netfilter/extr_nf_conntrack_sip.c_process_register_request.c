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
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct nf_nat_sip_hooks {int (* expect ) (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,struct nf_conntrack_expect*,unsigned int,unsigned int) ;} ;
struct nf_ct_sip_master {unsigned int register_cseq; } ;
struct TYPE_9__ {int expires; } ;
struct nf_conntrack_expect {int flags; int /*<<< orphan*/  helper; TYPE_4__ timeout; } ;
struct nf_conn {int status; TYPE_3__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  enum ip_conntrack_dir { ____Placeholder_ip_conntrack_dir } ip_conntrack_dir ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_10__ {int /*<<< orphan*/  helper; } ;
struct TYPE_6__ {union nf_inet_addr u3; } ;
struct TYPE_7__ {TYPE_1__ src; } ;
struct TYPE_8__ {TYPE_2__ tuple; } ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int HZ ; 
 int IPS_EXPECTED ; 
 int IPS_NAT_MASK ; 
 int NF_ACCEPT ; 
 int NF_CT_EXPECT_INACTIVE ; 
 int NF_CT_EXPECT_PERMANENT ; 
 int NF_DROP ; 
 int /*<<< orphan*/  SIP_EXPECT_SIGNALLING ; 
 int /*<<< orphan*/  SIP_HDR_CONTACT ; 
 int /*<<< orphan*/  SIP_HDR_EXPIRES ; 
 scalar_t__ ct_sip_get_header (struct nf_conn*,char const*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int ct_sip_parse_header_uri (struct nf_conn*,char const*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int*,unsigned int*,union nf_inet_addr*,int /*<<< orphan*/ *) ; 
 scalar_t__ ct_sip_parse_numerical_param (struct nf_conn*,char const*,unsigned int,unsigned int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ ct_sip_parse_transport (struct nf_conn*,char const*,unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 struct nf_conntrack_expect* nf_ct_expect_alloc (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_expect_init (struct nf_conntrack_expect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union nf_inet_addr*,union nf_inet_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 struct nf_conn* nf_ct_get (struct sk_buff*,int*) ; 
 int /*<<< orphan*/  nf_ct_helper_log (struct sk_buff*,struct nf_conn*,char*) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_inet_addr_cmp (union nf_inet_addr*,union nf_inet_addr*) ; 
 int /*<<< orphan*/  nf_nat_sip_hooks ; 
 TYPE_5__* nfct_help (struct nf_conn*) ; 
 struct nf_ct_sip_master* nfct_help_data (struct nf_conn*) ; 
 struct nf_nat_sip_hooks* rcu_dereference (int /*<<< orphan*/ ) ; 
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sip_direct_signalling ; 
 int sip_timeout ; 
 int stub1 (struct sk_buff*,unsigned int,unsigned int,char const**,unsigned int*,struct nf_conntrack_expect*,unsigned int,unsigned int) ; 

__attribute__((used)) static int process_register_request(struct sk_buff *skb, unsigned int protoff,
				    unsigned int dataoff,
				    const char **dptr, unsigned int *datalen,
				    unsigned int cseq)
{
	enum ip_conntrack_info ctinfo;
	struct nf_conn *ct = nf_ct_get(skb, &ctinfo);
	struct nf_ct_sip_master *ct_sip_info = nfct_help_data(ct);
	enum ip_conntrack_dir dir = CTINFO2DIR(ctinfo);
	unsigned int matchoff, matchlen;
	struct nf_conntrack_expect *exp;
	union nf_inet_addr *saddr, daddr;
	const struct nf_nat_sip_hooks *hooks;
	__be16 port;
	u8 proto;
	unsigned int expires = 0;
	int ret;

	/* Expected connections can not register again. */
	if (ct->status & IPS_EXPECTED)
		return NF_ACCEPT;

	/* We must check the expiration time: a value of zero signals the
	 * registrar to release the binding. We'll remove our expectation
	 * when receiving the new bindings in the response, but we don't
	 * want to create new ones.
	 *
	 * The expiration time may be contained in Expires: header, the
	 * Contact: header parameters or the URI parameters.
	 */
	if (ct_sip_get_header(ct, *dptr, 0, *datalen, SIP_HDR_EXPIRES,
			      &matchoff, &matchlen) > 0)
		expires = simple_strtoul(*dptr + matchoff, NULL, 10);

	ret = ct_sip_parse_header_uri(ct, *dptr, NULL, *datalen,
				      SIP_HDR_CONTACT, NULL,
				      &matchoff, &matchlen, &daddr, &port);
	if (ret < 0) {
		nf_ct_helper_log(skb, ct, "cannot parse contact");
		return NF_DROP;
	} else if (ret == 0)
		return NF_ACCEPT;

	/* We don't support third-party registrations */
	if (!nf_inet_addr_cmp(&ct->tuplehash[dir].tuple.src.u3, &daddr))
		return NF_ACCEPT;

	if (ct_sip_parse_transport(ct, *dptr, matchoff + matchlen, *datalen,
				   &proto) == 0)
		return NF_ACCEPT;

	if (ct_sip_parse_numerical_param(ct, *dptr,
					 matchoff + matchlen, *datalen,
					 "expires=", NULL, NULL, &expires) < 0) {
		nf_ct_helper_log(skb, ct, "cannot parse expires");
		return NF_DROP;
	}

	if (expires == 0) {
		ret = NF_ACCEPT;
		goto store_cseq;
	}

	exp = nf_ct_expect_alloc(ct);
	if (!exp) {
		nf_ct_helper_log(skb, ct, "cannot alloc expectation");
		return NF_DROP;
	}

	saddr = NULL;
	if (sip_direct_signalling)
		saddr = &ct->tuplehash[!dir].tuple.src.u3;

	nf_ct_expect_init(exp, SIP_EXPECT_SIGNALLING, nf_ct_l3num(ct),
			  saddr, &daddr, proto, NULL, &port);
	exp->timeout.expires = sip_timeout * HZ;
	exp->helper = nfct_help(ct)->helper;
	exp->flags = NF_CT_EXPECT_PERMANENT | NF_CT_EXPECT_INACTIVE;

	hooks = rcu_dereference(nf_nat_sip_hooks);
	if (hooks && ct->status & IPS_NAT_MASK)
		ret = hooks->expect(skb, protoff, dataoff, dptr, datalen,
				    exp, matchoff, matchlen);
	else {
		if (nf_ct_expect_related(exp, 0) != 0) {
			nf_ct_helper_log(skb, ct, "cannot add expectation");
			ret = NF_DROP;
		} else
			ret = NF_ACCEPT;
	}
	nf_ct_expect_put(exp);

store_cseq:
	if (ret == NF_ACCEPT)
		ct_sip_info->register_cseq = cseq;
	return ret;
}