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
struct skl_debug {void* fs; int /*<<< orphan*/ * dev; void* modules; struct skl* skl; } ;
struct skl {TYPE_2__* pci; TYPE_1__* component; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {void* debugfs_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 void* debugfs_create_dir (char*,void*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,void*,struct skl_debug*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct skl_debug* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soft_regs_ctrl_fops ; 

struct skl_debug *skl_debugfs_init(struct skl *skl)
{
	struct skl_debug *d;

	d = devm_kzalloc(&skl->pci->dev, sizeof(*d), GFP_KERNEL);
	if (!d)
		return NULL;

	/* create the debugfs dir with platform component's debugfs as parent */
	d->fs = debugfs_create_dir("dsp",
				   skl->component->debugfs_root);
	if (IS_ERR(d->fs) || !d->fs) {
		dev_err(&skl->pci->dev, "debugfs root creation failed\n");
		return NULL;
	}

	d->skl = skl;
	d->dev = &skl->pci->dev;

	/* now create the module dir */
	d->modules = debugfs_create_dir("modules", d->fs);
	if (IS_ERR(d->modules) || !d->modules) {
		dev_err(&skl->pci->dev, "modules debugfs create failed\n");
		goto err;
	}

	if (!debugfs_create_file("fw_soft_regs_rd", 0444, d->fs, d,
				 &soft_regs_ctrl_fops)) {
		dev_err(d->dev, "fw soft regs control debugfs init failed\n");
		goto err;
	}

	return d;

err:
	debugfs_remove_recursive(d->fs);
	return NULL;
}