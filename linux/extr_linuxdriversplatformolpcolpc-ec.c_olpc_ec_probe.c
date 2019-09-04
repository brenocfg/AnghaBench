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
struct platform_device {int dummy; } ;
struct olpc_ec_priv {int /*<<< orphan*/  dbgfs_dir; int /*<<< orphan*/  cmd_q_lock; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  worker; TYPE_1__* drv; } ;
struct TYPE_2__ {int (* probe ) (struct platform_device*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ec_driver ; 
 struct olpc_ec_priv* ec_priv ; 
 int /*<<< orphan*/  kfree (struct olpc_ec_priv*) ; 
 struct olpc_ec_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  olpc_ec_setup_debugfs () ; 
 int /*<<< orphan*/  olpc_ec_worker ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct olpc_ec_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct platform_device*) ; 

__attribute__((used)) static int olpc_ec_probe(struct platform_device *pdev)
{
	struct olpc_ec_priv *ec;
	int err;

	if (!ec_driver)
		return -ENODEV;

	ec = kzalloc(sizeof(*ec), GFP_KERNEL);
	if (!ec)
		return -ENOMEM;

	ec->drv = ec_driver;
	INIT_WORK(&ec->worker, olpc_ec_worker);
	mutex_init(&ec->cmd_lock);

	INIT_LIST_HEAD(&ec->cmd_q);
	spin_lock_init(&ec->cmd_q_lock);

	ec_priv = ec;
	platform_set_drvdata(pdev, ec);

	err = ec_driver->probe ? ec_driver->probe(pdev) : 0;
	if (err) {
		ec_priv = NULL;
		kfree(ec);
	} else {
		ec->dbgfs_dir = olpc_ec_setup_debugfs();
	}

	return err;
}