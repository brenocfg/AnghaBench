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
struct file {struct cros_ec_debugfs* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct cros_ec_debugfs {int /*<<< orphan*/  log_mutex; TYPE_1__ log_buffer; int /*<<< orphan*/  log_wq; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 scalar_t__ CIRC_CNT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  LOG_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t cros_ec_console_log_poll(struct file *file,
					     poll_table *wait)
{
	struct cros_ec_debugfs *debug_info = file->private_data;
	__poll_t mask = 0;

	poll_wait(file, &debug_info->log_wq, wait);

	mutex_lock(&debug_info->log_mutex);
	if (CIRC_CNT(debug_info->log_buffer.head,
		     debug_info->log_buffer.tail,
		     LOG_SIZE))
		mask |= EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&debug_info->log_mutex);

	return mask;
}