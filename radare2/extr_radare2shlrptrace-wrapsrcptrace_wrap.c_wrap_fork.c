#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  child_callback_user; int /*<<< orphan*/  (* child_callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ fork; } ;
struct TYPE_7__ {scalar_t__ fork_result; TYPE_2__ request; } ;
typedef  TYPE_3__ ptrace_wrap_instance ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ fork () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wrap_fork(ptrace_wrap_instance *inst) {
	pid_t r = fork();
	if (r == 0) {
		inst->request.fork.child_callback (inst->request.fork.child_callback_user);
	} else {
		inst->fork_result = r;
	}
}