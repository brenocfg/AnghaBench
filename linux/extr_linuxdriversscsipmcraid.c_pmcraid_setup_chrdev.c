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
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct pmcraid_instance {TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PMCRAID_DEVFILE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmcraid_class ; 
 int /*<<< orphan*/  pmcraid_fops ; 
 int pmcraid_get_minor () ; 
 int /*<<< orphan*/  pmcraid_major ; 
 int /*<<< orphan*/  pmcraid_release_minor (int) ; 

__attribute__((used)) static int pmcraid_setup_chrdev(struct pmcraid_instance *pinstance)
{
	int minor;
	int error;

	minor = pmcraid_get_minor();
	cdev_init(&pinstance->cdev, &pmcraid_fops);
	pinstance->cdev.owner = THIS_MODULE;

	error = cdev_add(&pinstance->cdev, MKDEV(pmcraid_major, minor), 1);

	if (error)
		pmcraid_release_minor(minor);
	else
		device_create(pmcraid_class, NULL, MKDEV(pmcraid_major, minor),
			      NULL, "%s%u", PMCRAID_DEVFILE, minor);
	return error;
}