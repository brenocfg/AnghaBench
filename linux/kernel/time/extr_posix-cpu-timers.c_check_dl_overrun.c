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
struct TYPE_2__ {scalar_t__ dl_overrun; } ;
struct task_struct {TYPE_1__ dl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_SIG_PRIV ; 
 int /*<<< orphan*/  SIGXCPU ; 
 int /*<<< orphan*/  __group_send_sig_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*) ; 

__attribute__((used)) static inline void check_dl_overrun(struct task_struct *tsk)
{
	if (tsk->dl.dl_overrun) {
		tsk->dl.dl_overrun = 0;
		__group_send_sig_info(SIGXCPU, SEND_SIG_PRIV, tsk);
	}
}