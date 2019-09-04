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
struct sock {scalar_t__ sk_shutdown; scalar_t__ sk_state; } ;

/* Variables and functions */
 scalar_t__ RCV_SHUTDOWN ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  lowcomms_data_ready (struct sock*) ; 
 int /*<<< orphan*/  lowcomms_write_space (struct sock*) ; 

__attribute__((used)) static void lowcomms_state_change(struct sock *sk)
{
	/* SCTP layer is not calling sk_data_ready when the connection
	 * is done, so we catch the signal through here. Also, it
	 * doesn't switch socket state when entering shutdown, so we
	 * skip the write in that case.
	 */
	if (sk->sk_shutdown) {
		if (sk->sk_shutdown == RCV_SHUTDOWN)
			lowcomms_data_ready(sk);
	} else if (sk->sk_state == TCP_ESTABLISHED) {
		lowcomms_write_space(sk);
	}
}