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
struct TYPE_2__ {scalar_t__ buf; } ;
struct cros_ec_debugfs {int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  log_poll_work; TYPE_1__ log_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cros_ec_cleanup_console_log(struct cros_ec_debugfs *debug_info)
{
	if (debug_info->log_buffer.buf) {
		cancel_delayed_work_sync(&debug_info->log_poll_work);
		mutex_destroy(&debug_info->log_mutex);
	}
}