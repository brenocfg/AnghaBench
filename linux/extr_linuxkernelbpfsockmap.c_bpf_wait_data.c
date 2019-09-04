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
struct sock {int /*<<< orphan*/  sk_receive_queue; } ;
struct smap_psock {int /*<<< orphan*/  ingress; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCKWQ_ASYNC_WAITDATA ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_clear_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_set_bit (int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int bpf_wait_data(struct sock *sk,
			 struct smap_psock *psk, int flags,
			 long timeo, int *err)
{
	int rc;

	DEFINE_WAIT_FUNC(wait, woken_wake_function);

	add_wait_queue(sk_sleep(sk), &wait);
	sk_set_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	rc = sk_wait_event(sk, &timeo,
			   !list_empty(&psk->ingress) ||
			   !skb_queue_empty(&sk->sk_receive_queue),
			   &wait);
	sk_clear_bit(SOCKWQ_ASYNC_WAITDATA, sk);
	remove_wait_queue(sk_sleep(sk), &wait);

	return rc;
}