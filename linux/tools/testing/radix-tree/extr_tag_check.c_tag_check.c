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

/* Variables and functions */
 int /*<<< orphan*/  __leak_check () ; 
 int /*<<< orphan*/  contract_checks () ; 
 int /*<<< orphan*/  extend_checks () ; 
 int /*<<< orphan*/  leak_check () ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  printv (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  simple_checks () ; 
 int /*<<< orphan*/  single_check () ; 
 int /*<<< orphan*/  thrash_tags () ; 

void tag_check(void)
{
	single_check();
	extend_checks();
	contract_checks();
	rcu_barrier();
	printv(2, "after extend_checks: %d allocated\n", nr_allocated);
	__leak_check();
	leak_check();
	rcu_barrier();
	printv(2, "after leak_check: %d allocated\n", nr_allocated);
	simple_checks();
	rcu_barrier();
	printv(2, "after simple_checks: %d allocated\n", nr_allocated);
	thrash_tags();
	rcu_barrier();
	printv(2, "after thrash_tags: %d allocated\n", nr_allocated);
}