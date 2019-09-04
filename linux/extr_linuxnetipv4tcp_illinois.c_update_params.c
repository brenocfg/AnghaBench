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
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {scalar_t__ snd_cwnd; } ;
struct sock {int dummy; } ;
struct illinois {scalar_t__ cnt_rtt; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_BASE ; 
 int /*<<< orphan*/  BETA_BASE ; 
 int /*<<< orphan*/  alpha (struct illinois*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avg_delay (struct illinois*) ; 
 int /*<<< orphan*/  beta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct illinois* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max_delay (struct illinois*) ; 
 int /*<<< orphan*/  rtt_reset (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ win_thresh ; 

__attribute__((used)) static void update_params(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct illinois *ca = inet_csk_ca(sk);

	if (tp->snd_cwnd < win_thresh) {
		ca->alpha = ALPHA_BASE;
		ca->beta = BETA_BASE;
	} else if (ca->cnt_rtt > 0) {
		u32 dm = max_delay(ca);
		u32 da = avg_delay(ca);

		ca->alpha = alpha(ca, da, dm);
		ca->beta = beta(da, dm);
	}

	rtt_reset(sk);
}