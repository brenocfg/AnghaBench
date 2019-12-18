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
struct sock {scalar_t__ sk_err; } ;
struct smc_sock {int wait_close_tx_prepared; int /*<<< orphan*/  conn; struct sock sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ECONNABORTED ; 
 scalar_t__ ECONNRESET ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_sleep (struct sock*) ; 
 int sk_wait_event (struct sock*,long*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_tx_prepared_sends (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static void smc_close_stream_wait(struct smc_sock *smc, long timeout)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	struct sock *sk = &smc->sk;

	if (!timeout)
		return;

	if (!smc_tx_prepared_sends(&smc->conn))
		return;

	smc->wait_close_tx_prepared = 1;
	add_wait_queue(sk_sleep(sk), &wait);
	while (!signal_pending(current) && timeout) {
		int rc;

		rc = sk_wait_event(sk, &timeout,
				   !smc_tx_prepared_sends(&smc->conn) ||
				   (sk->sk_err == ECONNABORTED) ||
				   (sk->sk_err == ECONNRESET),
				   &wait);
		if (rc)
			break;
	}
	remove_wait_queue(sk_sleep(sk), &wait);
	smc->wait_close_tx_prepared = 0;
}