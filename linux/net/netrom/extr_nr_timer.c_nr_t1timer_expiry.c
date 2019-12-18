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
struct timer_list {int dummy; } ;
struct sock {int dummy; } ;
struct nr_sock {int state; int /*<<< orphan*/  n2count; int /*<<< orphan*/  n2; struct sock sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIMEDOUT ; 
 int /*<<< orphan*/  NR_CONNREQ ; 
 int /*<<< orphan*/  NR_DISCREQ ; 
#define  NR_STATE_1 130 
#define  NR_STATE_2 129 
#define  NR_STATE_3 128 
 int /*<<< orphan*/  bh_lock_sock (struct sock*) ; 
 int /*<<< orphan*/  bh_unlock_sock (struct sock*) ; 
 struct nr_sock* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct nr_sock* nr ; 
 int /*<<< orphan*/  nr_disconnect (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_requeue_frames (struct sock*) ; 
 int /*<<< orphan*/  nr_start_t1timer (struct sock*) ; 
 int /*<<< orphan*/  nr_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1timer ; 

__attribute__((used)) static void nr_t1timer_expiry(struct timer_list *t)
{
	struct nr_sock *nr = from_timer(nr, t, t1timer);
	struct sock *sk = &nr->sock;

	bh_lock_sock(sk);
	switch (nr->state) {
	case NR_STATE_1:
		if (nr->n2count == nr->n2) {
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			return;
		} else {
			nr->n2count++;
			nr_write_internal(sk, NR_CONNREQ);
		}
		break;

	case NR_STATE_2:
		if (nr->n2count == nr->n2) {
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			return;
		} else {
			nr->n2count++;
			nr_write_internal(sk, NR_DISCREQ);
		}
		break;

	case NR_STATE_3:
		if (nr->n2count == nr->n2) {
			nr_disconnect(sk, ETIMEDOUT);
			bh_unlock_sock(sk);
			return;
		} else {
			nr->n2count++;
			nr_requeue_frames(sk);
		}
		break;
	}

	nr_start_t1timer(sk);
	bh_unlock_sock(sk);
}