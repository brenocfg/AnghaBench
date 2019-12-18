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
struct perf_event {int /*<<< orphan*/ * prog; TYPE_1__* tp_event; } ;
struct bpf_prog_array {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  prog_array; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  bpf_event_mutex ; 
 struct bpf_prog_array* bpf_event_rcu_dereference (int /*<<< orphan*/ ) ; 
 int bpf_prog_array_copy (struct bpf_prog_array*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bpf_prog_array**) ; 
 int /*<<< orphan*/  bpf_prog_array_delete_safe (struct bpf_prog_array*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_prog_array_free (struct bpf_prog_array*) ; 
 int /*<<< orphan*/  bpf_prog_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog_array*) ; 

void perf_event_detach_bpf_prog(struct perf_event *event)
{
	struct bpf_prog_array *old_array;
	struct bpf_prog_array *new_array;
	int ret;

	mutex_lock(&bpf_event_mutex);

	if (!event->prog)
		goto unlock;

	old_array = bpf_event_rcu_dereference(event->tp_event->prog_array);
	ret = bpf_prog_array_copy(old_array, event->prog, NULL, &new_array);
	if (ret == -ENOENT)
		goto unlock;
	if (ret < 0) {
		bpf_prog_array_delete_safe(old_array, event->prog);
	} else {
		rcu_assign_pointer(event->tp_event->prog_array, new_array);
		bpf_prog_array_free(old_array);
	}

	bpf_prog_put(event->prog);
	event->prog = NULL;

unlock:
	mutex_unlock(&bpf_event_mutex);
}