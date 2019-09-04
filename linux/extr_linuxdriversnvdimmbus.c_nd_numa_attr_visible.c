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
typedef  int /*<<< orphan*/  umode_t ;
struct kobject {int dummy; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_NUMA ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static umode_t nd_numa_attr_visible(struct kobject *kobj, struct attribute *a,
		int n)
{
	if (!IS_ENABLED(CONFIG_NUMA))
		return 0;

	return a->mode;
}