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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct esas2r_sas_nvram {int dummy; } ;
struct esas2r_request {int dummy; } ;
struct esas2r_adapter {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 struct esas2r_adapter* esas2r_adapter_from_kobj (struct kobject*) ; 
 struct esas2r_request* esas2r_alloc_request (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_free_request (struct esas2r_adapter*,struct esas2r_request*) ; 
 scalar_t__ esas2r_write_params (struct esas2r_adapter*,struct esas2r_request*,struct esas2r_sas_nvram*) ; 

__attribute__((used)) static ssize_t write_live_nvram(struct file *file, struct kobject *kobj,
				struct bin_attribute *attr,
				char *buf, loff_t off, size_t count)
{
	struct esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);
	struct esas2r_request *rq;
	int result = -EFAULT;

	rq = esas2r_alloc_request(a);
	if (rq == NULL)
		return -ENOMEM;

	if (esas2r_write_params(a, rq, (struct esas2r_sas_nvram *)buf))
		result = count;

	esas2r_free_request(a, rq);

	return result;
}