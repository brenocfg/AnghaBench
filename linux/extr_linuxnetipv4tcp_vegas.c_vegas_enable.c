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
struct vegas {int doing_vegas_now; int minRTT; scalar_t__ cntRTT; int /*<<< orphan*/  beg_snd_nxt; } ;
struct tcp_sock {int /*<<< orphan*/  snd_nxt; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 struct vegas* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void vegas_enable(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct vegas *vegas = inet_csk_ca(sk);

	/* Begin taking Vegas samples next time we send something. */
	vegas->doing_vegas_now = 1;

	/* Set the beginning of the next send window. */
	vegas->beg_snd_nxt = tp->snd_nxt;

	vegas->cntRTT = 0;
	vegas->minRTT = 0x7fffffff;
}