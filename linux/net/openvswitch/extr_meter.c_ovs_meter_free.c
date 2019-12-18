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
struct dp_meter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct dp_meter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void ovs_meter_free(struct dp_meter *meter)
{
	if (!meter)
		return;

	kfree_rcu(meter, rcu);
}