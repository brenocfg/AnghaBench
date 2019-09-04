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
struct workqueue_struct {int dummy; } ;
struct padata_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_possible_mask ; 
 int /*<<< orphan*/  lockdep_assert_cpus_held () ; 
 struct padata_instance* padata_alloc (struct workqueue_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct padata_instance *padata_alloc_possible(struct workqueue_struct *wq)
{
	lockdep_assert_cpus_held();
	return padata_alloc(wq, cpu_possible_mask, cpu_possible_mask);
}