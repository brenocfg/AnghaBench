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
struct nlattr {int dummy; } ;

/* Variables and functions */
 int LIBBPF_ERRNO__NLPARSE ; 
 int /*<<< orphan*/  NET_END_ARRAY (char*) ; 
 int /*<<< orphan*/  NET_START_ARRAY (char*,char*) ; 
 int TCA_ACT_MAX_PRIO ; 
 int do_dump_one_act (struct nlattr*) ; 
 scalar_t__ libbpf_nla_parse_nested (struct nlattr**,int,struct nlattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_bpf_act_dump(struct nlattr *attr)
{
	struct nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	int act, ret;

	if (libbpf_nla_parse_nested(tb, TCA_ACT_MAX_PRIO, attr, NULL) < 0)
		return -LIBBPF_ERRNO__NLPARSE;

	NET_START_ARRAY("act", " %s [");
	for (act = 0; act <= TCA_ACT_MAX_PRIO; act++) {
		ret = do_dump_one_act(tb[act]);
		if (ret)
			break;
	}
	NET_END_ARRAY("] ");

	return ret;
}