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
struct ida {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct ida mode_ids; } ;
struct TYPE_5__ {struct ida mode_ids; } ;
struct TYPE_4__ {struct ida mode_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (struct ida*,int) ; 
 scalar_t__ is_typec_partner (struct device*) ; 
 scalar_t__ is_typec_plug (struct device*) ; 
 TYPE_3__* to_typec_partner (struct device*) ; 
 TYPE_2__* to_typec_plug (struct device*) ; 
 TYPE_1__* to_typec_port (struct device*) ; 

__attribute__((used)) static void altmode_id_remove(struct device *dev, int id)
{
	struct ida *ids;

	if (is_typec_partner(dev))
		ids = &to_typec_partner(dev)->mode_ids;
	else if (is_typec_plug(dev))
		ids = &to_typec_plug(dev)->mode_ids;
	else
		ids = &to_typec_port(dev)->mode_ids;

	ida_simple_remove(ids, id);
}