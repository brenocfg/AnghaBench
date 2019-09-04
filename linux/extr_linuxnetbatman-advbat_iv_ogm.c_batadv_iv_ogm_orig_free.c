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
struct TYPE_2__ {int /*<<< orphan*/  bcast_own_sum; int /*<<< orphan*/  bcast_own; } ;
struct batadv_orig_node {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void batadv_iv_ogm_orig_free(struct batadv_orig_node *orig_node)
{
	kfree(orig_node->bat_iv.bcast_own);
	kfree(orig_node->bat_iv.bcast_own_sum);
}