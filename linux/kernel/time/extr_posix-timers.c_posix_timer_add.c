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
struct signal_struct {int posix_timer_id; } ;
struct k_itimer {int /*<<< orphan*/  t_hash; } ;
struct hlist_head {int dummy; } ;
struct TYPE_2__ {struct signal_struct* signal; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  __posix_timers_find (struct hlist_head*,struct signal_struct*,int) ; 
 TYPE_1__* current ; 
 size_t hash (struct signal_struct*,int) ; 
 int /*<<< orphan*/  hash_lock ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct hlist_head* posix_timers_hashtable ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int posix_timer_add(struct k_itimer *timer)
{
	struct signal_struct *sig = current->signal;
	int first_free_id = sig->posix_timer_id;
	struct hlist_head *head;
	int ret = -ENOENT;

	do {
		spin_lock(&hash_lock);
		head = &posix_timers_hashtable[hash(sig, sig->posix_timer_id)];
		if (!__posix_timers_find(head, sig, sig->posix_timer_id)) {
			hlist_add_head_rcu(&timer->t_hash, head);
			ret = sig->posix_timer_id;
		}
		if (++sig->posix_timer_id < 0)
			sig->posix_timer_id = 0;
		if ((sig->posix_timer_id == first_free_id) && (ret == -ENOENT))
			/* Loop over all possible ids completed */
			ret = -EAGAIN;
		spin_unlock(&hash_lock);
	} while (ret == -ENOENT);
	return ret;
}