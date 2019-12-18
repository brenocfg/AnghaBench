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
struct k_itimer {int /*<<< orphan*/  rcu; int /*<<< orphan*/  sigq; int /*<<< orphan*/  it_pid; int /*<<< orphan*/  t_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  k_itimer_rcu_free ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigqueue_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void release_posix_timer(struct k_itimer *tmr, int it_id_set)
{
	if (it_id_set) {
		unsigned long flags;
		spin_lock_irqsave(&hash_lock, flags);
		hlist_del_rcu(&tmr->t_hash);
		spin_unlock_irqrestore(&hash_lock, flags);
	}
	put_pid(tmr->it_pid);
	sigqueue_free(tmr->sigq);
	call_rcu(&tmr->rcu, k_itimer_rcu_free);
}