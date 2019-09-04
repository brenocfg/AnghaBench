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
struct pmcraid_instance {TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmcraid_class ; 
 int /*<<< orphan*/  pmcraid_major ; 
 int /*<<< orphan*/  pmcraid_release_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmcraid_release_chrdev(struct pmcraid_instance *pinstance)
{
	pmcraid_release_minor(MINOR(pinstance->cdev.dev));
	device_destroy(pmcraid_class,
		       MKDEV(pmcraid_major, MINOR(pinstance->cdev.dev)));
	cdev_del(&pinstance->cdev);
}