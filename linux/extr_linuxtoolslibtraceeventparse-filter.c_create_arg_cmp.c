#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;
struct filter_arg {TYPE_1__ num; int /*<<< orphan*/  type; } ;
typedef  enum filter_cmp_type { ____Placeholder_filter_cmp_type } filter_cmp_type ;

/* Variables and functions */
 int /*<<< orphan*/  FILTER_ARG_NUM ; 
 struct filter_arg* allocate_arg () ; 

__attribute__((used)) static struct filter_arg *
create_arg_cmp(enum filter_cmp_type ctype)
{
	struct filter_arg *arg;

	arg = allocate_arg();
	if (!arg)
		return NULL;

	/* Use NUM and change if necessary */
	arg->type = FILTER_ARG_NUM;
	arg->num.type = ctype;

	return arg;
}