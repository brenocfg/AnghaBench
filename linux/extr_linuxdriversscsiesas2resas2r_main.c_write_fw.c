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
struct esas2r_adapter {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct esas2r_adapter* esas2r_adapter_from_kobj (struct kobject*) ; 
 int /*<<< orphan*/  esas2r_write_fw (struct esas2r_adapter*,char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static ssize_t write_fw(struct file *file, struct kobject *kobj,
			struct bin_attribute *attr,
			char *buf, loff_t off, size_t count)
{
	struct esas2r_adapter *a = esas2r_adapter_from_kobj(kobj);

	return esas2r_write_fw(a, buf, off, count);
}