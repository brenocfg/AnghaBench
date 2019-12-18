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
struct mbochs_type {int mbytes; } ;
struct kobject {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int max_mbytes ; 
 struct mbochs_type* mbochs_find_type (struct kobject*) ; 
 int mbochs_used_mbytes ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
available_instances_show(struct kobject *kobj, struct device *dev, char *buf)
{
	const struct mbochs_type *type = mbochs_find_type(kobj);
	int count = (max_mbytes - mbochs_used_mbytes) / type->mbytes;

	return sprintf(buf, "%d\n", count);
}