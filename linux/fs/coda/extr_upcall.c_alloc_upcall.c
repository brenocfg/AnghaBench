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
struct TYPE_2__ {int opcode; int /*<<< orphan*/  uid; int /*<<< orphan*/  pgid; int /*<<< orphan*/  pid; } ;
union inputArgs {TYPE_1__ ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_pid_ns ; 
 int /*<<< orphan*/  init_user_ns ; 
 union inputArgs* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pgrp_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *alloc_upcall(int opcode, int size)
{
	union inputArgs *inp;

	inp = kvzalloc(size, GFP_KERNEL);
        if (!inp)
		return ERR_PTR(-ENOMEM);

        inp->ih.opcode = opcode;
	inp->ih.pid = task_pid_nr_ns(current, &init_pid_ns);
	inp->ih.pgid = task_pgrp_nr_ns(current, &init_pid_ns);
	inp->ih.uid = from_kuid(&init_user_ns, current_fsuid());

	return (void*)inp;
}