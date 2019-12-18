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
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long PM_QOS_CPU_DMA_LATENCY ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 long find_pm_qos_object_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 struct pm_qos_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_qos_add_request (struct pm_qos_request*,long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm_qos_power_open(struct inode *inode, struct file *filp)
{
	long pm_qos_class;

	pm_qos_class = find_pm_qos_object_by_minor(iminor(inode));
	if (pm_qos_class >= PM_QOS_CPU_DMA_LATENCY) {
		struct pm_qos_request *req = kzalloc(sizeof(*req), GFP_KERNEL);
		if (!req)
			return -ENOMEM;

		pm_qos_add_request(req, pm_qos_class, PM_QOS_DEFAULT_VALUE);
		filp->private_data = req;

		return 0;
	}
	return -EPERM;
}