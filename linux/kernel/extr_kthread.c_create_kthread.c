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
struct kthread_create_info {int /*<<< orphan*/  result; int /*<<< orphan*/  done; int /*<<< orphan*/  node; } ;
struct completion {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pref_node_fork; } ;

/* Variables and functions */
 int CLONE_FILES ; 
 int CLONE_FS ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 int SIGCHLD ; 
 int /*<<< orphan*/  complete (struct completion*) ; 
 TYPE_1__* current ; 
 int kernel_thread (int /*<<< orphan*/ ,struct kthread_create_info*,int) ; 
 int /*<<< orphan*/  kfree (struct kthread_create_info*) ; 
 int /*<<< orphan*/  kthread ; 
 struct completion* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void create_kthread(struct kthread_create_info *create)
{
	int pid;

#ifdef CONFIG_NUMA
	current->pref_node_fork = create->node;
#endif
	/* We want our own signal handler (we take no signals by default). */
	pid = kernel_thread(kthread, create, CLONE_FS | CLONE_FILES | SIGCHLD);
	if (pid < 0) {
		/* If user was SIGKILLed, I release the structure. */
		struct completion *done = xchg(&create->done, NULL);

		if (!done) {
			kfree(create);
			return;
		}
		create->result = ERR_PTR(pid);
		complete(done);
	}
}