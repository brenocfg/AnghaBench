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
struct illinois {int base_rtt; scalar_t__ rtt_above; scalar_t__ rtt_low; scalar_t__ acked; scalar_t__ max_rtt; int /*<<< orphan*/  beta; int /*<<< orphan*/  alpha; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_MAX ; 
 int /*<<< orphan*/  BETA_BASE ; 
 struct illinois* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  rtt_reset (struct sock*) ; 

__attribute__((used)) static void tcp_illinois_init(struct sock *sk)
{
	struct illinois *ca = inet_csk_ca(sk);

	ca->alpha = ALPHA_MAX;
	ca->beta = BETA_BASE;
	ca->base_rtt = 0x7fffffff;
	ca->max_rtt = 0;

	ca->acked = 0;
	ca->rtt_low = 0;
	ca->rtt_above = 0;

	rtt_reset(sk);
}