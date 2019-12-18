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
struct fib_rule_uid_range {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct fib_kuid_range {void* end; void* start; } ;

/* Variables and functions */
 size_t FRA_UID_RANGE ; 
 int /*<<< orphan*/  current_user_ns () ; 
 void* make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_data (struct nlattr*) ; 

__attribute__((used)) static struct fib_kuid_range nla_get_kuid_range(struct nlattr **tb)
{
	struct fib_rule_uid_range *in;
	struct fib_kuid_range out;

	in = (struct fib_rule_uid_range *)nla_data(tb[FRA_UID_RANGE]);

	out.start = make_kuid(current_user_ns(), in->start);
	out.end = make_kuid(current_user_ns(), in->end);

	return out;
}