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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd_clamp; } ;
struct sock {int dummy; } ;
struct hstcp {scalar_t__ ai; } ;

/* Variables and functions */
 struct hstcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void hstcp_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct hstcp *ca = inet_csk_ca(sk);

	ca->ai = 0;

	/* Ensure the MD arithmetic works.  This is somewhat pedantic,
	 * since I don't think we will see a cwnd this large. :) */
	tp->snd_cwnd_clamp = min_t(u32, tp->snd_cwnd_clamp, 0xffffffff/128);
}