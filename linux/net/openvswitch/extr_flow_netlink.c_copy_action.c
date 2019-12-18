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
struct sw_flow_actions {int dummy; } ;
struct nlattr {int /*<<< orphan*/  nla_len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nlattr*) ; 
 int NLA_ALIGN (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct nlattr*) ; 
 int /*<<< orphan*/  memcpy (struct nlattr*,struct nlattr const*,int) ; 
 struct nlattr* reserve_sfa_size (struct sw_flow_actions**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int copy_action(const struct nlattr *from,
		       struct sw_flow_actions **sfa, bool log)
{
	int totlen = NLA_ALIGN(from->nla_len);
	struct nlattr *to;

	to = reserve_sfa_size(sfa, from->nla_len, log);
	if (IS_ERR(to))
		return PTR_ERR(to);

	memcpy(to, from, totlen);
	return 0;
}