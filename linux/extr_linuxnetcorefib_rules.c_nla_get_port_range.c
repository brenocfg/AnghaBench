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
struct fib_rule_port_range {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fib_rule_port_range_valid (struct fib_rule_port_range const*) ; 
 struct fib_rule_port_range* nla_data (struct nlattr*) ; 

__attribute__((used)) static int nla_get_port_range(struct nlattr *pattr,
			      struct fib_rule_port_range *port_range)
{
	const struct fib_rule_port_range *pr = nla_data(pattr);

	if (!fib_rule_port_range_valid(pr))
		return -EINVAL;

	port_range->start = pr->start;
	port_range->end = pr->end;

	return 0;
}