#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tcp_sock {int snd_cwnd; } ;
struct sock {int dummy; } ;
struct hstcp {size_t ai; } ;
struct TYPE_2__ {int md; } ;

/* Variables and functions */
 TYPE_1__* hstcp_aimd_vals ; 
 struct hstcp* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  max (int,unsigned int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 hstcp_ssthresh(struct sock *sk)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	struct hstcp *ca = inet_csk_ca(sk);

	/* Do multiplicative decrease */
	return max(tp->snd_cwnd - ((tp->snd_cwnd * hstcp_aimd_vals[ca->ai].md) >> 8), 2U);
}