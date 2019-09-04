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
struct tcp_sock {int snd_cwnd; int snd_cwnd_clamp; int /*<<< orphan*/  srtt_us; } ;
struct sock {int dummy; } ;
struct hybla {int rho; int hybla_en; int /*<<< orphan*/  minrtt_us; scalar_t__ snd_cwnd_cents; scalar_t__ rho2_7ls; scalar_t__ rho_3ls; scalar_t__ rho2; } ;

/* Variables and functions */
 int /*<<< orphan*/  hybla_recalc_param (struct sock*) ; 
 struct hybla* inet_csk_ca (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void hybla_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct hybla *ca = inet_csk_ca(sk);

	ca->rho = 0;
	ca->rho2 = 0;
	ca->rho_3ls = 0;
	ca->rho2_7ls = 0;
	ca->snd_cwnd_cents = 0;
	ca->hybla_en = true;
	tp->snd_cwnd = 2;
	tp->snd_cwnd_clamp = 65535;

	/* 1st Rho measurement based on initial srtt */
	hybla_recalc_param(sk);

	/* set minimum rtt as this is the 1st ever seen */
	ca->minrtt_us = tp->srtt_us;
	tp->snd_cwnd = ca->rho;
}