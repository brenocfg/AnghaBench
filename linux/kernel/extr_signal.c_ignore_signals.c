#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_3__* sighand; } ;
struct TYPE_6__ {TYPE_2__* action; } ;
struct TYPE_4__ {int /*<<< orphan*/  sa_handler; } ;
struct TYPE_5__ {TYPE_1__ sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIG_IGN ; 
 int _NSIG ; 
 int /*<<< orphan*/  flush_signals (struct task_struct*) ; 

void ignore_signals(struct task_struct *t)
{
	int i;

	for (i = 0; i < _NSIG; ++i)
		t->sighand->action[i].sa.sa_handler = SIG_IGN;

	flush_signals(t);
}