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
struct padata_instance {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PADATA_CPU_PARALLEL ; 
 int PADATA_CPU_SERIAL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t bitmap_parse (char const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_cpumask_bits ; 
 size_t padata_set_cpumask (struct padata_instance*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t store_cpumask(struct padata_instance *pinst,
			     struct attribute *attr,
			     const char *buf, size_t count)
{
	cpumask_var_t new_cpumask;
	ssize_t ret;
	int mask_type;

	if (!alloc_cpumask_var(&new_cpumask, GFP_KERNEL))
		return -ENOMEM;

	ret = bitmap_parse(buf, count, cpumask_bits(new_cpumask),
			   nr_cpumask_bits);
	if (ret < 0)
		goto out;

	mask_type = !strcmp(attr->name, "serial_cpumask") ?
		PADATA_CPU_SERIAL : PADATA_CPU_PARALLEL;
	ret = padata_set_cpumask(pinst, mask_type, new_cpumask);
	if (!ret)
		ret = count;

out:
	free_cpumask_var(new_cpumask);
	return ret;
}