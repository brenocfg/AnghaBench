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
struct gcov_iterator {struct gcov_info* info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gcov_iterator* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_counter_active (struct gcov_info*) ; 
 int /*<<< orphan*/  struct_size (struct gcov_iterator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_info ; 

struct gcov_iterator *gcov_iter_new(struct gcov_info *info)
{
	struct gcov_iterator *iter;

	iter = kzalloc(struct_size(iter, type_info, num_counter_active(info)),
		       GFP_KERNEL);
	if (iter)
		iter->info = info;

	return iter;
}