#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bpf_func_proto {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 struct bpf_func_proto const bpf_probe_write_user_proto ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

__attribute__((used)) static const struct bpf_func_proto *bpf_get_probe_write_proto(void)
{
	pr_warn_ratelimited("%s[%d] is installing a program with bpf_probe_write_user helper that may corrupt user memory!",
			    current->comm, task_pid_nr(current));

	return &bpf_probe_write_user_proto;
}