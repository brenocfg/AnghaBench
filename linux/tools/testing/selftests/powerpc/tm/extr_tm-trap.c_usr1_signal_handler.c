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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int exit_from_pong ; 

void usr1_signal_handler(int signo, siginfo_t *si, void *not_used)
{
	/* Got a USR1 signal from ping(), so just tell pong() to exit */
	exit_from_pong = 1;
}