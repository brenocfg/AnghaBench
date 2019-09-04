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
struct cros_ec_dev {TYPE_1__* debug_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  cros_ec_cleanup_console_log (TYPE_1__*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 

void cros_ec_debugfs_remove(struct cros_ec_dev *ec)
{
	if (!ec->debug_info)
		return;

	debugfs_remove_recursive(ec->debug_info->dir);
	cros_ec_cleanup_console_log(ec->debug_info);
}