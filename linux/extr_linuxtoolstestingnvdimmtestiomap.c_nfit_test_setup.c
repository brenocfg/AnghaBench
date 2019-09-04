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
typedef  int /*<<< orphan*/  nfit_test_lookup_fn ;
typedef  int /*<<< orphan*/  nfit_test_evaluate_dsm_fn ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  evaluate_dsm; int /*<<< orphan*/  nfit_test_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  iomap_head ; 
 TYPE_1__ iomap_ops ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nfit_test_setup(nfit_test_lookup_fn lookup,
		nfit_test_evaluate_dsm_fn evaluate)
{
	iomap_ops.nfit_test_lookup = lookup;
	iomap_ops.evaluate_dsm = evaluate;
	list_add_rcu(&iomap_ops.list, &iomap_head);
}