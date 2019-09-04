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
struct task_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  disassociate_ctty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_clear_tty (struct task_struct*) ; 

void no_tty(void)
{
	/* FIXME: Review locking here. The tty_lock never covered any race
	   between a new association and proc_clear_tty but possible we need
	   to protect against this anyway */
	struct task_struct *tsk = current;
	disassociate_ctty(0);
	proc_clear_tty(tsk);
}