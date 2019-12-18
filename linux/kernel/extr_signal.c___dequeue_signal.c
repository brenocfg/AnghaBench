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
struct sigpending {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  kernel_siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  collect_signal (int,struct sigpending*,int /*<<< orphan*/ *,int*) ; 
 int next_signal (struct sigpending*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __dequeue_signal(struct sigpending *pending, sigset_t *mask,
			kernel_siginfo_t *info, bool *resched_timer)
{
	int sig = next_signal(pending, mask);

	if (sig)
		collect_signal(sig, pending, info, resched_timer);
	return sig;
}