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
struct westwood {scalar_t__ snd_una; int /*<<< orphan*/  bk; } ;
struct tcp_sock {scalar_t__ snd_una; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct westwood* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  update_rtt_min (struct westwood*) ; 
 int /*<<< orphan*/  westwood_update_window (struct sock*) ; 

__attribute__((used)) static inline void westwood_fast_bw(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct westwood *w = inet_csk_ca(sk);

	westwood_update_window(sk);

	w->bk += tp->snd_una - w->snd_una;
	w->snd_una = tp->snd_una;
	update_rtt_min(w);
}