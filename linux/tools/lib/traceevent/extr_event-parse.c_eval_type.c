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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct tep_print_arg {scalar_t__ type; TYPE_1__ typecast; } ;

/* Variables and functions */
 scalar_t__ TEP_PRINT_TYPE ; 
 int /*<<< orphan*/  do_warning (char*) ; 
 unsigned long long eval_type_str (unsigned long long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long long
eval_type(unsigned long long val, struct tep_print_arg *arg, int pointer)
{
	if (arg->type != TEP_PRINT_TYPE) {
		do_warning("expected type argument");
		return 0;
	}

	return eval_type_str(val, arg->typecast.type, pointer);
}