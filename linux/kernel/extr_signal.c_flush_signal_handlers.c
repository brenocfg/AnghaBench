#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_2__* sighand; } ;
struct TYPE_3__ {scalar_t__ sa_handler; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/ * sa_restorer; scalar_t__ sa_flags; } ;
struct k_sigaction {TYPE_1__ sa; } ;
struct TYPE_4__ {struct k_sigaction* action; } ;

/* Variables and functions */
 scalar_t__ SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int _NSIG ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

void
flush_signal_handlers(struct task_struct *t, int force_default)
{
	int i;
	struct k_sigaction *ka = &t->sighand->action[0];
	for (i = _NSIG ; i != 0 ; i--) {
		if (force_default || ka->sa.sa_handler != SIG_IGN)
			ka->sa.sa_handler = SIG_DFL;
		ka->sa.sa_flags = 0;
#ifdef __ARCH_HAS_SA_RESTORER
		ka->sa.sa_restorer = NULL;
#endif
		sigemptyset(&ka->sa.sa_mask);
		ka++;
	}
}