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
struct tty_struct {scalar_t__ link; } ;
struct pid {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SIGINT ; 
 int SIGQUIT ; 
 int SIGTSTP ; 
 int /*<<< orphan*/  kill_pgrp (struct pid*,int,int) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 struct pid* tty_get_pgrp (scalar_t__) ; 

__attribute__((used)) static int pty_signal(struct tty_struct *tty, int sig)
{
	struct pid *pgrp;

	if (sig != SIGINT && sig != SIGQUIT && sig != SIGTSTP)
		return -EINVAL;

	if (tty->link) {
		pgrp = tty_get_pgrp(tty->link);
		if (pgrp)
			kill_pgrp(pgrp, sig, 1);
		put_pid(pgrp);
	}
	return 0;
}