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
struct user_struct {int /*<<< orphan*/  sigpending; } ;
struct task_struct {int dummy; } ;
struct sigqueue {struct user_struct* user; scalar_t__ flags; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  user; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RLIMIT_SIGPENDING ; 
 TYPE_1__* __task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_uid (struct user_struct*) ; 
 struct user_struct* get_uid (int /*<<< orphan*/ ) ; 
 struct sigqueue* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_dropped_signal (int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sigqueue_cachep ; 
 scalar_t__ task_rlimit (struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sigqueue *
__sigqueue_alloc(int sig, struct task_struct *t, gfp_t flags, int override_rlimit)
{
	struct sigqueue *q = NULL;
	struct user_struct *user;

	/*
	 * Protect access to @t credentials. This can go away when all
	 * callers hold rcu read lock.
	 */
	rcu_read_lock();
	user = get_uid(__task_cred(t)->user);
	atomic_inc(&user->sigpending);
	rcu_read_unlock();

	if (override_rlimit ||
	    atomic_read(&user->sigpending) <=
			task_rlimit(t, RLIMIT_SIGPENDING)) {
		q = kmem_cache_alloc(sigqueue_cachep, flags);
	} else {
		print_dropped_signal(sig);
	}

	if (unlikely(q == NULL)) {
		atomic_dec(&user->sigpending);
		free_uid(user);
	} else {
		INIT_LIST_HEAD(&q->list);
		q->flags = 0;
		q->user = user;
	}

	return q;
}