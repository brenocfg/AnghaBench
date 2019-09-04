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
struct pm_qos_request {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct pm_qos_request* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pm_qos_request*) ; 
 int /*<<< orphan*/  pm_qos_remove_request (struct pm_qos_request*) ; 

__attribute__((used)) static int pm_qos_power_release(struct inode *inode, struct file *filp)
{
	struct pm_qos_request *req;

	req = filp->private_data;
	pm_qos_remove_request(req);
	kfree(req);

	return 0;
}