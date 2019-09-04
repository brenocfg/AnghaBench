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
struct sugov_tunables {int /*<<< orphan*/  attr_set; } ;
struct sugov_policy {int /*<<< orphan*/  tunables_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct sugov_tunables* global_tunables ; 
 int /*<<< orphan*/  gov_attr_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  have_governor_per_policy () ; 
 struct sugov_tunables* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sugov_tunables *sugov_tunables_alloc(struct sugov_policy *sg_policy)
{
	struct sugov_tunables *tunables;

	tunables = kzalloc(sizeof(*tunables), GFP_KERNEL);
	if (tunables) {
		gov_attr_set_init(&tunables->attr_set, &sg_policy->tunables_hook);
		if (!have_governor_per_policy())
			global_tunables = tunables;
	}
	return tunables;
}