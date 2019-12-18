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
struct klp_shadow {int /*<<< orphan*/  data; int /*<<< orphan*/  obj; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  (* klp_shadow_dtor_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  hash_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct klp_shadow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 

__attribute__((used)) static void klp_shadow_free_struct(struct klp_shadow *shadow,
				   klp_shadow_dtor_t dtor)
{
	hash_del_rcu(&shadow->node);
	if (dtor)
		dtor(shadow->obj, shadow->data);
	kfree_rcu(shadow, rcu_head);
}