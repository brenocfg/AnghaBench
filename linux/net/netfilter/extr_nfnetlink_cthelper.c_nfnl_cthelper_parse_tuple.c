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
struct nlattr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  protonum; } ;
struct TYPE_3__ {int /*<<< orphan*/  l3num; } ;
struct nf_conntrack_tuple {TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NFCTH_TUPLE_L3PROTONUM ; 
 size_t NFCTH_TUPLE_L4PROTONUM ; 
 int /*<<< orphan*/  NFCTH_TUPLE_MAX ; 
 int /*<<< orphan*/  memset (struct nf_conntrack_tuple*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfnl_cthelper_tuple_pol ; 
 int /*<<< orphan*/  nla_get_be16 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_get_u8 (struct nlattr*) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfnl_cthelper_parse_tuple(struct nf_conntrack_tuple *tuple,
			  const struct nlattr *attr)
{
	int err;
	struct nlattr *tb[NFCTH_TUPLE_MAX+1];

	err = nla_parse_nested_deprecated(tb, NFCTH_TUPLE_MAX, attr,
					  nfnl_cthelper_tuple_pol, NULL);
	if (err < 0)
		return err;

	if (!tb[NFCTH_TUPLE_L3PROTONUM] || !tb[NFCTH_TUPLE_L4PROTONUM])
		return -EINVAL;

	/* Not all fields are initialized so first zero the tuple */
	memset(tuple, 0, sizeof(struct nf_conntrack_tuple));

	tuple->src.l3num = ntohs(nla_get_be16(tb[NFCTH_TUPLE_L3PROTONUM]));
	tuple->dst.protonum = nla_get_u8(tb[NFCTH_TUPLE_L4PROTONUM]);

	return 0;
}