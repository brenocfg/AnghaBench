#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct powercap_zone_constraint_ops {scalar_t__ get_min_time_window_us; scalar_t__ get_max_time_window_us; scalar_t__ get_min_power_uw; scalar_t__ get_max_power_uw; scalar_t__ get_name; int /*<<< orphan*/  set_time_window_us; int /*<<< orphan*/  get_time_window_us; int /*<<< orphan*/  set_power_limit_uw; int /*<<< orphan*/  get_power_limit_uw; } ;
struct powercap_zone_constraint {struct powercap_zone_constraint_ops const* ops; int /*<<< orphan*/  id; } ;
struct powercap_zone {int zone_attr_count; int /*<<< orphan*/ ** zone_dev_attrs; int /*<<< orphan*/  const_id_cnt; struct powercap_zone_constraint* constraints; } ;
struct TYPE_15__ {int /*<<< orphan*/  attr; } ;
struct TYPE_14__ {int /*<<< orphan*/  attr; } ;
struct TYPE_13__ {int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {int /*<<< orphan*/  attr; } ;
struct TYPE_11__ {int /*<<< orphan*/  attr; } ;
struct TYPE_10__ {int /*<<< orphan*/  attr; } ;
struct TYPE_9__ {int /*<<< orphan*/  attr; } ;
struct TYPE_16__ {TYPE_7__ min_time_window_attr; TYPE_6__ max_time_window_attr; TYPE_5__ min_power_attr; TYPE_4__ max_power_attr; TYPE_3__ name_attr; TYPE_2__ time_window_attr; TYPE_1__ power_limit_attr; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_8__* constraint_attrs ; 

__attribute__((used)) static int create_constraints(struct powercap_zone *power_zone,
			int nr_constraints,
			const struct powercap_zone_constraint_ops *const_ops)
{
	int i;
	int ret = 0;
	int count;
	struct powercap_zone_constraint *pconst;

	if (!power_zone || !const_ops || !const_ops->get_power_limit_uw ||
					!const_ops->set_power_limit_uw ||
					!const_ops->get_time_window_us ||
					!const_ops->set_time_window_us)
		return -EINVAL;

	count = power_zone->zone_attr_count;
	for (i = 0; i < nr_constraints; ++i) {
		pconst = &power_zone->constraints[i];
		pconst->ops = const_ops;
		pconst->id = power_zone->const_id_cnt;
		power_zone->const_id_cnt++;
		power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].power_limit_attr.attr;
		power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].time_window_attr.attr;
		if (pconst->ops->get_name)
			power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].name_attr.attr;
		if (pconst->ops->get_max_power_uw)
			power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].max_power_attr.attr;
		if (pconst->ops->get_min_power_uw)
			power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].min_power_attr.attr;
		if (pconst->ops->get_max_time_window_us)
			power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].max_time_window_attr.attr;
		if (pconst->ops->get_min_time_window_us)
			power_zone->zone_dev_attrs[count++] =
				&constraint_attrs[i].min_time_window_attr.attr;
	}
	power_zone->zone_attr_count = count;

	return ret;
}