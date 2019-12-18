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

/* Variables and functions */
 int /*<<< orphan*/  is_stopped () ; 
 scalar_t__ nr_sk_threads ; 
 scalar_t__ threads_done () ; 
 int /*<<< orphan*/  threads_err () ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static bool wait_for_threads_done(void)
{
	while (threads_done() != nr_sk_threads && !is_stopped() &&
	       !threads_err())
		usleep(50);

	return !is_stopped() && !threads_err();
}