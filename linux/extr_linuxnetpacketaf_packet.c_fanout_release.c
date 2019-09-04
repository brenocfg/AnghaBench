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
struct sock {int dummy; } ;
struct packet_sock {struct packet_fanout* fanout; } ;
struct packet_fanout {int /*<<< orphan*/  list; int /*<<< orphan*/  sk_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  fanout_mutex ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct packet_fanout *fanout_release(struct sock *sk)
{
	struct packet_sock *po = pkt_sk(sk);
	struct packet_fanout *f;

	mutex_lock(&fanout_mutex);
	f = po->fanout;
	if (f) {
		po->fanout = NULL;

		if (refcount_dec_and_test(&f->sk_ref))
			list_del(&f->list);
		else
			f = NULL;
	}
	mutex_unlock(&fanout_mutex);

	return f;
}