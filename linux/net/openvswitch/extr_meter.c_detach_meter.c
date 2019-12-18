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
struct dp_meter {int /*<<< orphan*/  dp_hash_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_OVSL () ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void detach_meter(struct dp_meter *meter)
{
	ASSERT_OVSL();
	if (meter)
		hlist_del_rcu(&meter->dp_hash_node);
}