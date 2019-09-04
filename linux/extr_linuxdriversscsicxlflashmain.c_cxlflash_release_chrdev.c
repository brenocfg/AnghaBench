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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct cxlflash_cfg {TYPE_1__ cdev; int /*<<< orphan*/ * chardev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  cxlflash_put_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cxlflash_release_chrdev(struct cxlflash_cfg *cfg)
{
	device_unregister(cfg->chardev);
	cfg->chardev = NULL;
	cdev_del(&cfg->cdev);
	cxlflash_put_minor(MINOR(cfg->cdev.dev));
}