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
struct sugov_tunables {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * global_tunables ; 
 int /*<<< orphan*/  have_governor_per_policy () ; 
 int /*<<< orphan*/  kfree (struct sugov_tunables*) ; 

__attribute__((used)) static void sugov_tunables_free(struct sugov_tunables *tunables)
{
	if (!have_governor_per_policy())
		global_tunables = NULL;

	kfree(tunables);
}