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
struct aa_ns {TYPE_1__* unconfined; int /*<<< orphan*/  parent; int /*<<< orphan*/  labels; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  aa_free_profile (TYPE_1__*) ; 
 int /*<<< orphan*/  aa_labelset_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_policy_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aa_put_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct aa_ns*) ; 

void aa_free_ns(struct aa_ns *ns)
{
	if (!ns)
		return;

	aa_policy_destroy(&ns->base);
	aa_labelset_destroy(&ns->labels);
	aa_put_ns(ns->parent);

	ns->unconfined->ns = NULL;
	aa_free_profile(ns->unconfined);
	kzfree(ns);
}