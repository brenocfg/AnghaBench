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
struct sock {int dummy; } ;
struct bbr {scalar_t__ full_bw_cnt; scalar_t__ full_bw; } ;
struct TYPE_2__ {int /*<<< orphan*/  snd_cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbr_reset_lt_bw_sampling (struct sock*) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 bbr_undo_cwnd(struct sock *sk)
{
	struct bbr *bbr = inet_csk_ca(sk);

	bbr->full_bw = 0;   /* spurious slow-down; reset full pipe detection */
	bbr->full_bw_cnt = 0;
	bbr_reset_lt_bw_sampling(sk);
	return tcp_sk(sk)->snd_cwnd;
}