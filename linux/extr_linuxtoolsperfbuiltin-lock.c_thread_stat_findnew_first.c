#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct thread_stat {int /*<<< orphan*/  rb; int /*<<< orphan*/  seq_list; int /*<<< orphan*/  tid; } ;
struct TYPE_3__ {int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_stat_findnew ; 
 int /*<<< orphan*/  thread_stat_findnew_after_first ; 
 TYPE_1__ thread_stats ; 
 struct thread_stat* zalloc (int) ; 

__attribute__((used)) static struct thread_stat *thread_stat_findnew_first(u32 tid)
{
	struct thread_stat *st;

	st = zalloc(sizeof(struct thread_stat));
	if (!st) {
		pr_err("memory allocation failed\n");
		return NULL;
	}
	st->tid = tid;
	INIT_LIST_HEAD(&st->seq_list);

	rb_link_node(&st->rb, NULL, &thread_stats.rb_node);
	rb_insert_color(&st->rb, &thread_stats);

	thread_stat_findnew = thread_stat_findnew_after_first;
	return st;
}