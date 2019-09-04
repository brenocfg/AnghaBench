#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  dbf ;
struct TYPE_5__ {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int /*<<< orphan*/ ,char*) ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int chsc_async (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int chsc_examine_irb (TYPE_1__*) ; 
 int /*<<< orphan*/  chsc_lock ; 
 int /*<<< orphan*/  chsc_log_command (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chsc_ready_for_use ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * on_close_chsc_area ; 
 int /*<<< orphan*/  on_close_mutex ; 
 TYPE_1__* on_close_request ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chsc_release(struct inode *inode, struct file *filp)
{
	char dbf[13];
	int ret;

	mutex_lock(&on_close_mutex);
	if (!on_close_chsc_area)
		goto out_unlock;
	init_completion(&on_close_request->completion);
	CHSC_LOG(0, "on_close");
	chsc_log_command(on_close_chsc_area);
	spin_lock_irq(&chsc_lock);
	ret = chsc_async(on_close_chsc_area, on_close_request);
	spin_unlock_irq(&chsc_lock);
	if (ret == -EINPROGRESS) {
		wait_for_completion(&on_close_request->completion);
		ret = chsc_examine_irb(on_close_request);
	}
	snprintf(dbf, sizeof(dbf), "relret:%d", ret);
	CHSC_LOG(0, dbf);
	free_page((unsigned long)on_close_chsc_area);
	on_close_chsc_area = NULL;
	kfree(on_close_request);
	on_close_request = NULL;
out_unlock:
	mutex_unlock(&on_close_mutex);
	atomic_inc(&chsc_ready_for_use);
	return 0;
}