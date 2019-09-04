#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pmcraid_instance {int /*<<< orphan*/  aen_queue_lock; int /*<<< orphan*/  aen_queue; } ;
struct file {struct pmcraid_instance* private_data; } ;

/* Variables and functions */
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pmcraid_chr_fasync(int fd, struct file *filep, int mode)
{
	struct pmcraid_instance *pinstance;
	int rc;

	pinstance = filep->private_data;
	mutex_lock(&pinstance->aen_queue_lock);
	rc = fasync_helper(fd, filep, mode, &pinstance->aen_queue);
	mutex_unlock(&pinstance->aen_queue_lock);

	return rc;
}