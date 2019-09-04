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
struct TYPE_6__ {int /*<<< orphan*/ * _errno; int /*<<< orphan*/  data; int /*<<< orphan*/  addr; int /*<<< orphan*/  pid; int /*<<< orphan*/  request; } ;
struct TYPE_5__ {TYPE_2__ ptrace; } ;
struct TYPE_7__ {TYPE_1__ request; int /*<<< orphan*/  ptrace_result; } ;
typedef  TYPE_3__ ptrace_wrap_instance ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wrap_ptrace(ptrace_wrap_instance *inst) {
	inst->ptrace_result = ptrace (
			inst->request.ptrace.request,
			inst->request.ptrace.pid,
			inst->request.ptrace.addr,
			inst->request.ptrace.data);
	if (inst->request.ptrace._errno) {
		*inst->request.ptrace._errno = errno;
	}
}