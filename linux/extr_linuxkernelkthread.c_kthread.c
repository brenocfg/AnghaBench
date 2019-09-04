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
struct kthread_create_info {int (* threadfn ) (void*) ;TYPE_1__* result; int /*<<< orphan*/  done; void* data; } ;
struct kthread {int /*<<< orphan*/  flags; int /*<<< orphan*/  exited; int /*<<< orphan*/  parked; void* data; } ;
struct completion {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vfork_done; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOMEM ; 
 TYPE_1__* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KTHREAD_SHOULD_STOP ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __kthread_parkme (struct kthread*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_kthread_ready () ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  do_exit (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kthread_create_info*) ; 
 struct kthread* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_kthread_struct (struct kthread*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct completion* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kthread(void *_create)
{
	/* Copy data: it's on kthread's stack */
	struct kthread_create_info *create = _create;
	int (*threadfn)(void *data) = create->threadfn;
	void *data = create->data;
	struct completion *done;
	struct kthread *self;
	int ret;

	self = kzalloc(sizeof(*self), GFP_KERNEL);
	set_kthread_struct(self);

	/* If user was SIGKILLed, I release the structure. */
	done = xchg(&create->done, NULL);
	if (!done) {
		kfree(create);
		do_exit(-EINTR);
	}

	if (!self) {
		create->result = ERR_PTR(-ENOMEM);
		complete(done);
		do_exit(-ENOMEM);
	}

	self->data = data;
	init_completion(&self->exited);
	init_completion(&self->parked);
	current->vfork_done = &self->exited;

	/* OK, tell user we're spawned, wait for stop or wakeup */
	__set_current_state(TASK_UNINTERRUPTIBLE);
	create->result = current;
	complete(done);
	schedule();

	ret = -EINTR;
	if (!test_bit(KTHREAD_SHOULD_STOP, &self->flags)) {
		cgroup_kthread_ready();
		__kthread_parkme(self);
		ret = threadfn(data);
	}
	do_exit(ret);
}