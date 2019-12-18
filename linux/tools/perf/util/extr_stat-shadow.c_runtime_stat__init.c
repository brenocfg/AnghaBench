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
struct rblist {int /*<<< orphan*/  node_delete; int /*<<< orphan*/  node_new; int /*<<< orphan*/  node_cmp; } ;
struct runtime_stat {struct rblist value_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  rblist__init (struct rblist*) ; 
 int /*<<< orphan*/  saved_value_cmp ; 
 int /*<<< orphan*/  saved_value_delete ; 
 int /*<<< orphan*/  saved_value_new ; 

void runtime_stat__init(struct runtime_stat *st)
{
	struct rblist *rblist = &st->value_list;

	rblist__init(rblist);
	rblist->node_cmp = saved_value_cmp;
	rblist->node_new = saved_value_new;
	rblist->node_delete = saved_value_delete;
}