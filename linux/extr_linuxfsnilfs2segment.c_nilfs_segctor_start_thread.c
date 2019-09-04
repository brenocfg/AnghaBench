#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int dummy; } ;
struct nilfs_sc_info {int /*<<< orphan*/ * sc_task; int /*<<< orphan*/  sc_wait_task; int /*<<< orphan*/  sc_super; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int PTR_ERR (struct task_struct*) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct nilfs_sc_info*,char*) ; 
 int /*<<< orphan*/  nilfs_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nilfs_segctor_thread ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_segctor_start_thread(struct nilfs_sc_info *sci)
{
	struct task_struct *t;

	t = kthread_run(nilfs_segctor_thread, sci, "segctord");
	if (IS_ERR(t)) {
		int err = PTR_ERR(t);

		nilfs_msg(sci->sc_super, KERN_ERR,
			  "error %d creating segctord thread", err);
		return err;
	}
	wait_event(sci->sc_wait_task, sci->sc_task != NULL);
	return 0;
}