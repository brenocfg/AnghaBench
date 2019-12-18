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
typedef  int /*<<< orphan*/  u32 ;
struct thread_stat {int /*<<< orphan*/  seq_list; int /*<<< orphan*/  tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct thread_stat* thread_stat_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_stat_insert (struct thread_stat*) ; 
 struct thread_stat* zalloc (int) ; 

__attribute__((used)) static struct thread_stat *thread_stat_findnew_after_first(u32 tid)
{
	struct thread_stat *st;

	st = thread_stat_find(tid);
	if (st)
		return st;

	st = zalloc(sizeof(struct thread_stat));
	if (!st) {
		pr_err("memory allocation failed\n");
		return NULL;
	}

	st->tid = tid;
	INIT_LIST_HEAD(&st->seq_list);

	thread_stat_insert(st);

	return st;
}