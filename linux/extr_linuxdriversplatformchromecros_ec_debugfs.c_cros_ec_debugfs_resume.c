#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cros_ec_dev {TYPE_2__* debug_info; } ;
struct TYPE_3__ {scalar_t__ buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  log_poll_work; TYPE_1__ log_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cros_ec_debugfs_resume(struct cros_ec_dev *ec)
{
	if (ec->debug_info && ec->debug_info->log_buffer.buf)
		schedule_delayed_work(&ec->debug_info->log_poll_work, 0);
}