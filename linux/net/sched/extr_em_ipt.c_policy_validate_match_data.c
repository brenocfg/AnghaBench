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
typedef  scalar_t__ u8 ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NF_INET_PRE_ROUTING ; 
 size_t TCA_EM_IPT_HOOK ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int policy_validate_match_data(struct nlattr **tb, u8 mrev)
{
	if (mrev != 0) {
		pr_err("only policy match revision 0 supported");
		return -EINVAL;
	}

	if (nla_get_u32(tb[TCA_EM_IPT_HOOK]) != NF_INET_PRE_ROUTING) {
		pr_err("policy can only be matched on NF_INET_PRE_ROUTING");
		return -EINVAL;
	}

	return 0;
}