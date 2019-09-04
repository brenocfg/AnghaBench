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
struct TYPE_5__ {int /*<<< orphan*/  user; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ func; } ;
struct TYPE_7__ {TYPE_2__ request; int /*<<< orphan*/  func_result; } ;
typedef  TYPE_3__ ptrace_wrap_instance ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wrap_func(ptrace_wrap_instance *inst) {
	inst->func_result = inst->request.func.func (inst->request.func.user);
}