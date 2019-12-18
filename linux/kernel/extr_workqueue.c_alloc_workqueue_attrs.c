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
struct workqueue_attrs {int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_workqueue_attrs (struct workqueue_attrs*) ; 
 struct workqueue_attrs* kzalloc (int,int /*<<< orphan*/ ) ; 

struct workqueue_attrs *alloc_workqueue_attrs(void)
{
	struct workqueue_attrs *attrs;

	attrs = kzalloc(sizeof(*attrs), GFP_KERNEL);
	if (!attrs)
		goto fail;
	if (!alloc_cpumask_var(&attrs->cpumask, GFP_KERNEL))
		goto fail;

	cpumask_copy(attrs->cpumask, cpu_possible_mask);
	return attrs;
fail:
	free_workqueue_attrs(attrs);
	return NULL;
}