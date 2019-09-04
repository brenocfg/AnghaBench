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
struct user_struct {int /*<<< orphan*/  unix_inflight; } ;
struct unix_sock {int /*<<< orphan*/  link; int /*<<< orphan*/  inflight; } ;
struct sock {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_long_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_gc_lock ; 
 struct sock* unix_get_socket (struct file*) ; 
 struct unix_sock* unix_sk (struct sock*) ; 
 int /*<<< orphan*/  unix_tot_inflight ; 

void unix_notinflight(struct user_struct *user, struct file *fp)
{
	struct sock *s = unix_get_socket(fp);

	spin_lock(&unix_gc_lock);

	if (s) {
		struct unix_sock *u = unix_sk(s);

		BUG_ON(!atomic_long_read(&u->inflight));
		BUG_ON(list_empty(&u->link));

		if (atomic_long_dec_and_test(&u->inflight))
			list_del_init(&u->link);
		unix_tot_inflight--;
	}
	user->unix_inflight--;
	spin_unlock(&unix_gc_lock);
}