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
struct TYPE_4__ {int /*<<< orphan*/  signal; } ;
struct task_struct {TYPE_3__* signal; TYPE_1__ pending; } ;
struct TYPE_5__ {int /*<<< orphan*/  signal; } ;
struct TYPE_6__ {TYPE_2__ shared_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sigkill_pending(struct task_struct *tsk)
{
	return sigismember(&tsk->pending.signal, SIGKILL) ||
	       sigismember(&tsk->signal->shared_pending.signal, SIGKILL);
}