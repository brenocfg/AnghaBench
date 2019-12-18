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
struct TYPE_3__ {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir ; 
 TYPE_1__ netdev_notifier_err_inject ; 
 int /*<<< orphan*/  notifier_err_inject_dir ; 
 int /*<<< orphan*/  notifier_err_inject_init (char*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priority ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netdev_err_inject_init(void)
{
	int err;

	dir = notifier_err_inject_init("netdev", notifier_err_inject_dir,
				       &netdev_notifier_err_inject, priority);
	if (IS_ERR(dir))
		return PTR_ERR(dir);

	err = register_netdevice_notifier(&netdev_notifier_err_inject.nb);
	if (err)
		debugfs_remove_recursive(dir);

	return err;
}