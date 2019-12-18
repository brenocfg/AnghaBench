#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  delta_user_count; int /*<<< orphan*/  user_count; } ;
struct objagg_obj {TYPE_3__* parent; TYPE_1__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  delta_user_count; } ;
struct TYPE_6__ {TYPE_2__ stats; } ;

/* Variables and functions */

__attribute__((used)) static void objagg_obj_stats_inc(struct objagg_obj *objagg_obj)
{
	objagg_obj->stats.user_count++;
	objagg_obj->stats.delta_user_count++;
	if (objagg_obj->parent)
		objagg_obj->parent->stats.delta_user_count++;
}