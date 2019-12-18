#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct cpumask* pcpu; struct cpumask* cbcpu; } ;
struct padata_instance {int /*<<< orphan*/  lock; TYPE_1__ cpumask; } ;
struct cpumask {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  cpumask_bits (struct cpumask*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_cpu_ids ; 
 scalar_t__ snprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_cpumask(struct padata_instance *pinst,
			    struct attribute *attr,  char *buf)
{
	struct cpumask *cpumask;
	ssize_t len;

	mutex_lock(&pinst->lock);
	if (!strcmp(attr->name, "serial_cpumask"))
		cpumask = pinst->cpumask.cbcpu;
	else
		cpumask = pinst->cpumask.pcpu;

	len = snprintf(buf, PAGE_SIZE, "%*pb\n",
		       nr_cpu_ids, cpumask_bits(cpumask));
	mutex_unlock(&pinst->lock);
	return len < PAGE_SIZE ? len : -EINVAL;
}