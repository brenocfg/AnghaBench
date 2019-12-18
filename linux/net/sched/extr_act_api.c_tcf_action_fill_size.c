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
struct tc_action {TYPE_1__* ops; } ;
struct TYPE_2__ {size_t (* get_fill_size ) (struct tc_action const*) ;} ;

/* Variables and functions */
 size_t stub1 (struct tc_action const*) ; 
 size_t tcf_action_shared_attrs_size (struct tc_action const*) ; 

__attribute__((used)) static size_t tcf_action_fill_size(const struct tc_action *act)
{
	size_t sz = tcf_action_shared_attrs_size(act);

	if (act->ops->get_fill_size)
		return act->ops->get_fill_size(act) + sz;
	return sz;
}