#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  tuple; int /*<<< orphan*/  helper; } ;
struct nf_conn {TYPE_5__* tuplehash; int /*<<< orphan*/  status; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  addr ;
typedef  scalar_t__ __be16 ;
struct TYPE_13__ {int /*<<< orphan*/  rasAddress; } ;
struct TYPE_8__ {scalar_t__ port; } ;
struct TYPE_9__ {TYPE_1__ udp; } ;
struct TYPE_10__ {int /*<<< orphan*/  u3; TYPE_2__ u; } ;
struct TYPE_11__ {TYPE_3__ src; } ;
struct TYPE_12__ {TYPE_4__ tuple; } ;
typedef  TYPE_6__ GatekeeperConfirm ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPS_EXPECTED_BIT ; 
 int /*<<< orphan*/  NF_CT_EXPECT_CLASS_DEFAULT ; 
 int /*<<< orphan*/  get_h225_addr (struct nf_conn*,unsigned char*,int /*<<< orphan*/ *,union nf_inet_addr*,scalar_t__*) ; 
 int /*<<< orphan*/  memcmp (union nf_inet_addr*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nf_conntrack_helper_ras ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 struct nf_conntrack_expect* nf_ct_expect_alloc (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_expect_init (struct nf_conntrack_expect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union nf_inet_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int process_gcf(struct sk_buff *skb, struct nf_conn *ct,
		       enum ip_conntrack_info ctinfo,
		       unsigned int protoff,
		       unsigned char **data, GatekeeperConfirm *gcf)
{
	int dir = CTINFO2DIR(ctinfo);
	int ret = 0;
	__be16 port;
	union nf_inet_addr addr;
	struct nf_conntrack_expect *exp;

	pr_debug("nf_ct_ras: GCF\n");

	if (!get_h225_addr(ct, *data, &gcf->rasAddress, &addr, &port))
		return 0;

	/* Registration port is the same as discovery port */
	if (!memcmp(&addr, &ct->tuplehash[dir].tuple.src.u3, sizeof(addr)) &&
	    port == ct->tuplehash[dir].tuple.src.u.udp.port)
		return 0;

	/* Avoid RAS expectation loops. A GCF is never expected. */
	if (test_bit(IPS_EXPECTED_BIT, &ct->status))
		return 0;

	/* Need new expect */
	if ((exp = nf_ct_expect_alloc(ct)) == NULL)
		return -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_UDP, NULL, &port);
	exp->helper = nf_conntrack_helper_ras;

	if (nf_ct_expect_related(exp, 0) == 0) {
		pr_debug("nf_ct_ras: expect RAS ");
		nf_ct_dump_tuple(&exp->tuple);
	} else
		ret = -1;

	nf_ct_expect_put(exp);

	return ret;
}