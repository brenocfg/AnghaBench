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
struct sock {int dummy; } ;
struct bbr {void* cwnd_gain; void* pacing_gain; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBR_STARTUP ; 
 void* bbr_high_gain ; 
 struct bbr* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void bbr_reset_startup_mode(struct sock *sk)
{
	struct bbr *bbr = inet_csk_ca(sk);

	bbr->mode = BBR_STARTUP;
	bbr->pacing_gain = bbr_high_gain;
	bbr->cwnd_gain	 = bbr_high_gain;
}