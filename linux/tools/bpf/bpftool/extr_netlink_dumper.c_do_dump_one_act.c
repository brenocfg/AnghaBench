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
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 size_t TCA_ACT_OPTIONS ; 
 int do_bpf_dump_one_act (struct nlattr*) ; 
 int /*<<< orphan*/  libbpf_nla_data (struct nlattr*) ; 
 scalar_t__ libbpf_nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int do_dump_one_act(struct nlattr *attr)
{
	struct nlattr *tb[TCA_ACT_MAX + 1];

	if (!attr)
		return 0;

	if (libbpf_nla_parse_nested(tb, TCA_ACT_MAX, attr, NULL) < 0)
		return -LIBBPF_ERRNO__NLPARSE;

	if (tb[TCA_ACT_KIND] &&
	    strcmp(libbpf_nla_data(tb[TCA_ACT_KIND]), "bpf") == 0)
		return do_bpf_dump_one_act(tb[TCA_ACT_OPTIONS]);

	return 0;
}