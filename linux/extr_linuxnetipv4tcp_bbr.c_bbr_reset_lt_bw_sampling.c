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
struct bbr {int lt_is_sampling; scalar_t__ lt_use_bw; scalar_t__ lt_bw; } ;

/* Variables and functions */
 int /*<<< orphan*/  bbr_reset_lt_bw_sampling_interval (struct sock*) ; 
 struct bbr* inet_csk_ca (struct sock*) ; 

__attribute__((used)) static void bbr_reset_lt_bw_sampling(struct sock *sk)
{
	struct bbr *bbr = inet_csk_ca(sk);

	bbr->lt_bw = 0;
	bbr->lt_use_bw = 0;
	bbr->lt_is_sampling = false;
	bbr_reset_lt_bw_sampling_interval(sk);
}