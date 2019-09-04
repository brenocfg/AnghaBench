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
typedef  int u32 ;
struct westwood {int /*<<< orphan*/  bk; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int CA_ACK_SLOWPATH ; 
 struct westwood* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  update_rtt_min (struct westwood*) ; 
 scalar_t__ westwood_acked_count (struct sock*) ; 
 int /*<<< orphan*/  westwood_fast_bw (struct sock*) ; 
 int /*<<< orphan*/  westwood_update_window (struct sock*) ; 

__attribute__((used)) static void tcp_westwood_ack(struct sock *sk, u32 ack_flags)
{
	if (ack_flags & CA_ACK_SLOWPATH) {
		struct westwood *w = inet_csk_ca(sk);

		westwood_update_window(sk);
		w->bk += westwood_acked_count(sk);

		update_rtt_min(w);
		return;
	}

	westwood_fast_bw(sk);
}