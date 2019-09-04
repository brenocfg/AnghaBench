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
struct device {int dummy; } ;

/* Variables and functions */
 int device_for_each_child (struct device*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_pmem_forget_poison_check ; 

__attribute__((used)) static int nd_ns_forget_poison_check(struct device *dev, void *data)
{
	return device_for_each_child(dev, data, nd_pmem_forget_poison_check);
}