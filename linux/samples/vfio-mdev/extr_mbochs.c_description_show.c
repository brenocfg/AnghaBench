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
 struct mbochs_type* mbochs_find_type (struct kobject*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t
description_show(struct kobject *kobj, struct device *dev, char *buf)
{
	const struct mbochs_type *type = mbochs_find_type(kobj);

	return sprintf(buf, "virtual display, %d MB video memory\n",
		       type ? type->mbytes  : 0);
}