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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pacing_timer; } ;

/* Variables and functions */
 scalar_t__ hrtimer_is_queued (int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_needs_internal_pacing (struct sock const*) ; 
 TYPE_1__* tcp_sk (struct sock const*) ; 

__attribute__((used)) static bool tcp_pacing_check(const struct sock *sk)
{
	return tcp_needs_internal_pacing(sk) &&
	       hrtimer_is_queued(&tcp_sk(sk)->pacing_timer);
}