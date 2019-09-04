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
struct tcp_sock {int snd_cwnd; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  max (int,unsigned int) ; 
 int nv_loss_dec_factor ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 tcpnv_recalc_ssthresh(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);

	return max((tp->snd_cwnd * nv_loss_dec_factor) >> 10, 2U);
}