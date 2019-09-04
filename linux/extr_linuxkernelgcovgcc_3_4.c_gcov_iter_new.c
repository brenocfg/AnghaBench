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
struct type_info {int dummy; } ;
struct gcov_iterator {struct gcov_info* info; } ;
struct gcov_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gcov_iterator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int num_counter_active (struct gcov_info*) ; 

struct gcov_iterator *gcov_iter_new(struct gcov_info *info)
{
	struct gcov_iterator *iter;

	iter = kzalloc(sizeof(struct gcov_iterator) +
		       num_counter_active(info) * sizeof(struct type_info),
		       GFP_KERNEL);
	if (iter)
		iter->info = info;

	return iter;
}