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
struct cdev {struct kobject kobj; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */

__attribute__((used)) static struct kobject *exact_match(dev_t dev, int *part, void *data)
{
	struct cdev *p = data;
	return &p->kobj;
}