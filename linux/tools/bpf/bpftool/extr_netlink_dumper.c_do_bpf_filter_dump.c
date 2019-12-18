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
 int /*<<< orphan*/  NET_DUMP_STR (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NET_DUMP_UINT (char*,char*,int /*<<< orphan*/ ) ; 
 size_t TCA_BPF_ACT ; 
 size_t TCA_BPF_ID ; 
 int /*<<< orphan*/  TCA_BPF_MAX ; 
 size_t TCA_BPF_NAME ; 
 int do_bpf_act_dump (struct nlattr*) ; 
 int /*<<< orphan*/  libbpf_nla_getattr_str (struct nlattr*) ; 
 int /*<<< orphan*/  libbpf_nla_getattr_u32 (struct nlattr*) ; 
 scalar_t__ libbpf_nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_bpf_filter_dump(struct nlattr *attr)
{
	struct nlattr *tb[TCA_BPF_MAX + 1];
	int ret;

	if (libbpf_nla_parse_nested(tb, TCA_BPF_MAX, attr, NULL) < 0)
		return -LIBBPF_ERRNO__NLPARSE;

	if (tb[TCA_BPF_NAME])
		NET_DUMP_STR("name", " %s",
			     libbpf_nla_getattr_str(tb[TCA_BPF_NAME]));
	if (tb[TCA_BPF_ID])
		NET_DUMP_UINT("id", " id %u",
			      libbpf_nla_getattr_u32(tb[TCA_BPF_ID]));
	if (tb[TCA_BPF_ACT]) {
		ret = do_bpf_act_dump(tb[TCA_BPF_ACT]);
		if (ret)
			return ret;
	}

	return 0;
}