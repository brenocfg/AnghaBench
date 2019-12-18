#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union nf_inet_addr {int dummy; } nf_inet_addr ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_expect {int /*<<< orphan*/  tuple; int /*<<< orphan*/  helper; int /*<<< orphan*/  flags; } ;
struct nf_conn {TYPE_3__* tuplehash; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_9__ {int /*<<< orphan*/  callSignalAddress; } ;
struct TYPE_6__ {int /*<<< orphan*/  u3; } ;
struct TYPE_7__ {TYPE_1__ src; } ;
struct TYPE_8__ {TYPE_2__ tuple; } ;
typedef  TYPE_4__ LocationConfirm ;

/* Variables and functions */
 int CTINFO2DIR (int) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  NF_CT_EXPECT_CLASS_DEFAULT ; 
 int /*<<< orphan*/  NF_CT_EXPECT_PERMANENT ; 
 int /*<<< orphan*/  get_h225_addr (struct nf_conn*,unsigned char*,int /*<<< orphan*/ *,union nf_inet_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_helper_q931 ; 
 int /*<<< orphan*/  nf_ct_dump_tuple (int /*<<< orphan*/ *) ; 
 struct nf_conntrack_expect* nf_ct_expect_alloc (struct nf_conn*) ; 
 int /*<<< orphan*/  nf_ct_expect_init (struct nf_conntrack_expect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union nf_inet_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_expect_put (struct nf_conntrack_expect*) ; 
 scalar_t__ nf_ct_expect_related (struct nf_conntrack_expect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_l3num (struct nf_conn*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int process_lcf(struct sk_buff *skb, struct nf_conn *ct,
		       enum ip_conntrack_info ctinfo,
		       unsigned int protoff,
		       unsigned char **data, LocationConfirm *lcf)
{
	int dir = CTINFO2DIR(ctinfo);
	int ret = 0;
	__be16 port;
	union nf_inet_addr addr;
	struct nf_conntrack_expect *exp;

	pr_debug("nf_ct_ras: LCF\n");

	if (!get_h225_addr(ct, *data, &lcf->callSignalAddress,
			   &addr, &port))
		return 0;

	/* Need new expect for call signal */
	if ((exp = nf_ct_expect_alloc(ct)) == NULL)
		return -1;
	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, nf_ct_l3num(ct),
			  &ct->tuplehash[!dir].tuple.src.u3, &addr,
			  IPPROTO_TCP, NULL, &port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->helper = nf_conntrack_helper_q931;

	if (nf_ct_expect_related(exp, 0) == 0) {
		pr_debug("nf_ct_ras: expect Q.931 ");
		nf_ct_dump_tuple(&exp->tuple);
	} else
		ret = -1;

	nf_ct_expect_put(exp);

	/* Ignore rasAddress */

	return ret;
}